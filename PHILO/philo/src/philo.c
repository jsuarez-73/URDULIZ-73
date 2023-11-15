/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:38 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/15 17:32:32 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	ft_date_update(void)
{
	struct timeval	tday;

	if (!gettimeofday(&tday, NULL))
		return (tday.tv_sec * 1000 + tday.tv_usec / 1000);
	return (0);
}

char	*ft_set_emoji(t_state state)
{
	if (state == DIED)
		return (HEADSTONE);
	else if (state == EATING)
		return (SPAGHETTI);
	else if (state == THINKING)
		return (BULB);
	else if (state == SLEEPING)
		return (NAPPING);
	else if (state == FORKING_TWO)
		return (FORK_AND_PLATE);
	else if (state == FORKING_ONE)
		return (FORK);
	return (NULL);
}

void	ft_push_log(t_philo *phs, char *log, t_state state)
{
	suseconds_t	now;
	char		*emoji;
	
	pthread_mutex_lock(phs->l_log);
	now = ft_date_update();
	if (phs->state != state && *phs->signal == SIGCONT)
	{
		phs->state = state;
		if (state == DIED)
			*phs->signal = SIGDIED;
		emoji = ft_set_emoji(state);
		printf("%lu %u %s %s\n", now, phs->id, log, emoji);
	}
	pthread_mutex_unlock(phs->l_log);
}

void	ft_eat(t_philo *phs)
{
	pthread_mutex_lock(&phs->fork);
	ft_push_log(phs, "has taken a fork", FORKING_TWO);
	phs->free = BUSY;
	pthread_mutex_unlock(phs->l_start);
	phs->timer.l_eat = ft_date_update();
	ft_push_log(phs, "is eating", EATING);
	usleep(phs->timer.t_eat);
	phs->ntme++; 
	phs->back->free = FREE;
	pthread_mutex_unlock(&phs->back->fork);
	phs->free = FREE;
	pthread_mutex_unlock(&phs->fork);
	ft_push_log(phs, "is sleeping", SLEEPING);
	usleep(phs->timer.t_slp);
	ft_push_log(phs, "is thinking", THINKING);
	usleep(phs->timer.t_think);
}

void	ft_live(t_philo *phs)
{
	pthread_mutex_lock(phs->l_start);
	if (phs->back->free)
	{
		pthread_mutex_lock(&phs->back->fork);
		phs->back->free = BUSY;
		ft_push_log(phs, "has taken a fork", FORKING_ONE);
		if (phs->free)
			ft_eat(phs);
		else
		{
			pthread_mutex_unlock(phs->l_start);
			phs->back->free = FREE;
			pthread_mutex_unlock(&phs->back->fork);
		}
	}
	else
	{
		ft_push_log(phs, "is thinking", THINKING);
		pthread_mutex_unlock(phs->l_start);
	}
}

short	ft_everyone_has_eaten(t_gdata *gdt, t_philo *phs)
{
	if (phs->ntme == *(gdt->params + N_EPME) && !phs->ticked)
	{
		phs->ticked = 1;
		gdt->tphe++;
		// printf("Thread#:%u\tntme:%d\ttphe:%d\n", phs->id, phs->ntme, gdt->tphe);
		gdt->signal = SIGNTME;
	}
	if (gdt->tphe == *(gdt->params + N_PHILO))
		return (1);
	return (0);
}

short	ft_someone_has_death(t_philo *phs, suseconds_t delta_time)
{
	if (*phs->signal != SIGCONT)
		return (1);
	if (delta_time >= phs->timer.t_die)
	{
		ft_push_log(phs, "died", DIED);
		return (1);
	}
	return (0);
}
short	ft_all_lifes(t_gdata *gdt, t_philo *phs)
{
	suseconds_t	now;
	suseconds_t	delta_time;

	pthread_mutex_lock(&gdt->l_check);
	now = ft_date_update();
	delta_time = (now - phs->timer.l_eat) * MILI_TO_MICRO;
	// printf("Thread#:%u\tdelta_time: %lu\tl_eat:%lu\tnow:%lu\n", phs->id, delta_time, phs->timer.l_eat, now);
	if (ft_someone_has_death(phs, delta_time))
	{
		pthread_mutex_unlock(&gdt->l_check);
		return (0);
	}
	if (*(gdt->params + N_EPME))
	{
		if (ft_everyone_has_eaten(gdt, phs))
		{
			pthread_mutex_unlock(&gdt->l_check);
			return (0);
		}
	}
	pthread_mutex_unlock(&gdt->l_check);
	return (1);
}

void	ft_set_philo(t_gdata **gdt, t_philo **phs)
{
	pthread_mutex_lock(&(*gdt)->l_start);
	*phs = (*gdt)->phs + --(*gdt)->markers;
	(*phs)->id = (*gdt)->markers + 1;
	(*phs)->free = FREE;
	(*phs)->ntme = 0;
	(*phs)->ticked = 0;
	(*phs)->timer.t_die = *((*gdt)->params + T_DIE) * MILI_TO_MICRO;
	(*phs)->timer.t_eat = *((*gdt)->params + T_EAT) * MILI_TO_MICRO;
	(*phs)->timer.t_slp = *((*gdt)->params + T_SLP) * MILI_TO_MICRO;
	(*phs)->timer.t_think = (*phs)->timer.t_die / MILI_TO_MICRO;
	(*phs)->state = STARTING;
	(*phs)->signal = &(*gdt)->signal;
	(*phs)->l_start = &(*gdt)->l_start;
	(*phs)->l_log = &(*gdt)->l_log;
	pthread_mutex_init(&(*phs)->fork, NULL);
	pthread_mutex_unlock(&(*gdt)->l_start);
}

void	*ft_life_philo(void *arg)
{
	t_gdata			*gdt;
	t_philo			*phs;
	short			wait;

	gdt = (t_gdata *)arg;
	wait = 1;
	ft_set_philo(&gdt, &phs);
	while (wait)
	{
		pthread_mutex_lock(&gdt->l_start);
		if (!gdt->start)
			wait = 0;
		pthread_mutex_unlock(&gdt->l_start);
	}
	while(ft_all_lifes(gdt, phs))
		ft_live(phs);
	pthread_mutex_destroy(&phs->fork);
	return (NULL);
}

void	ft_memory_flush(t_gdata *gdt)
{
	if (gdt->id)
		free(gdt->id);
	if (gdt->phs)
		free(gdt->phs);
	pthread_mutex_destroy(&gdt->l_start);
	pthread_mutex_destroy(&gdt->l_check);
	pthread_mutex_destroy(&gdt->l_log);
}

void	ft_init_gdata(t_gdata *gdt, int n_f)
{
	gdt->id = (pthread_t *)malloc(sizeof(pthread_t) * (n_f + 1));
	gdt->phs = (t_philo *)malloc(sizeof(t_philo) * n_f);
	if (!gdt->id || !gdt->phs)
		exit(-1);
	*(gdt->id + n_f) = 0; //Last zero to dont need the n_philo constant.
	pthread_mutex_init(&gdt->l_start, NULL); //Mutex to start race all together
	pthread_mutex_init(&gdt->l_check, NULL); //Mutex to check global deaths
	pthread_mutex_init(&gdt->l_log, NULL); //Mutex to push log in terminal
	gdt->start = 1;
	gdt->tphe = 0;
	gdt->signal = SIGCONT;
	gdt->markers = n_f; //Markers to identify each thread.
	gdt->phs->back = gdt->phs + n_f - 1; //The first one points to the last one
}

void	ft_set_lifetime(t_gdata *gdt, t_philo *last_phs)
{
	t_philo	*off_phs;

	off_phs = gdt->phs;
	pthread_mutex_lock(&gdt->l_check);
	while (off_phs < last_phs)
	{
		off_phs->timer.l_eat = ft_date_update();
		off_phs++;
	}
	pthread_mutex_unlock(&gdt->l_check);
}

short	ft_wait_all_init(t_gdata *gdt, int n_f)
{
	t_philo			*last_phs;
	t_philo			*phs;

	last_phs = gdt->phs + n_f;
	phs = gdt->phs;
	pthread_mutex_lock(&gdt->l_start);
	while (phs < last_phs)
	{
		if (!phs->signal)
		{
			pthread_mutex_unlock(&gdt->l_start);
			return (1);
		}
		else if (phs + 1 == last_phs && phs->signal)
		{
			ft_set_lifetime(gdt, last_phs);
			gdt->start = 0; //set the signal to start the race.
			pthread_mutex_unlock(&gdt->l_start);
			return (0);
		}
		phs++;
	}
	pthread_mutex_unlock(&gdt->l_start);
	return (1);
}

void	ft_create_threads(t_gdata *gdt, int n_f)
{
	int	all;

	all = n_f;
	while (n_f--)
	{
		pthread_create(gdt->id + n_f, NULL, ft_life_philo, gdt);
		if (n_f >= 1)
			(gdt->phs + n_f)->back = (gdt->phs + n_f - 1);
	}
	while (ft_wait_all_init(gdt, all)) ;
}

void	ft_join_threads(t_gdata *gdt, int n_f)
{
	while (n_f--)
		pthread_join(*(gdt->id + n_f), NULL);
}
/*USAR HELGRIN MANANA PARA DETECTAR LOS ERRORES ENCONTRADOS POR ESTA TOOL,
AL PARECER OCURREN LOCK ABOUT ALREADY LOCKED.*/
int	main(int argc, char **argv)
{
	t_gdata	gdt;
	int		n_f;
	
	ft_init_args(argc, argv, gdt.params);
	n_f = *(gdt.params + N_PHILO);
	ft_init_gdata(&gdt, n_f);
	ft_create_threads(&gdt, n_f);
	ft_join_threads(&gdt, n_f);
	/*Cuando todos retornen, flush the memory.*/
	ft_memory_flush(&gdt);
	return (0);
}
