/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:38 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/14 17:36:15 by jsuarez-         ###   ########.fr       */
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
		{
			emoji = HEADSTONE;
			*phs->signal = SIGDIED;
		}
		else if (state == EATING)
			emoji = SPAGHETTI;
		else if (state == THINKING)
			emoji = BULB;
		else if (state == SLEEPING)
			emoji = NAPPING;
		else if (state == FORKING_TWO)
			emoji = FORK_AND_PLATE;
		else if (state == FORKING_ONE)
			emoji = FORK;
		printf("%lu %u %s %s\n", now, phs->id, log, emoji);
	}
	pthread_mutex_unlock(phs->l_log);
}
/*EL thread al parecer no esta durmiendo con la setencia usleep
Response: SI duerme, solo que algun hilo despierto imprime el estado de todos.
*/
void	ft_eat(t_philo *phs)
{
	pthread_mutex_lock(&phs->fork);
	ft_push_log(phs, "has taken a fork", FORKING_TWO);
	phs->free = BUSY;
	pthread_mutex_unlock(phs->l_start);
	ft_push_log(phs, "is eating", EATING);
	usleep(phs->timer.t_eat);
	phs->timer.l_eat = ft_date_update();
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
/*	if (phs->back->free) //Esta operacion parece corresponder a una operacion atomica
	{ //movq	%rdi, -8(%rbp)*/
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

/*Quizas agregar tantos bucles para determinar si todos han comido puede
ser contra producente y consumir muchos recursos, esta operacion se
ejecuta tantas veces como hilos hayan, con lo cual es bastante costosa
y agregarle carga hace que sea insuficiente a la hora de detemrinar si todos
han comido.*/
int	ft_all_lifes(t_gdata *gdt)
{
	t_philo		*phs;
	suseconds_t	now;
	suseconds_t	delta_time;

	pthread_mutex_lock(&gdt->l_check);
	phs = gdt->phs;
	now = ft_date_update();
	while (phs < (gdt->phs + *(gdt->params + N_PHILO)))
	{
		delta_time = (now - phs->timer.l_eat) * MILI_TO_MICRO;
		// printf("Thread#:%u\tdelta_time: %lu\tl_eat:%lu\tnow:%lu\n", phs->id, delta_time, phs->timer.l_eat, now);
		if (delta_time >= phs->timer.t_die)
		{
			ft_push_log(phs, "died", DIED);
			pthread_mutex_unlock(&gdt->l_check);
			return (0);
		}
		// if (phs->ntme == *(gdt->params + N_EPME))
		// 	gdt->tphe++;
		phs++;
	}
	// if (gdt->tphe == *(gdt->params + N_PHILO))
	// {
	// 	pthread_mutex_unlock(&gdt->l_check);
	// 	return (0);
	// }
	// gdt->tphe = 0;
	pthread_mutex_unlock(&gdt->l_check);
	return (1);
}

void	*ft_life_philo(void *arg)
{
	t_gdata			*gdt;
	t_philo			*phs;

	gdt = (t_gdata *)arg;
	pthread_mutex_lock(&gdt->l_start);
	phs = gdt->phs + --gdt->markers;
	phs->id = gdt->markers + 1;
	phs->free = FREE;
	phs->ntme = 0;
	phs->timer.t_die = *(gdt->params + T_DIE) * MILI_TO_MICRO;
	phs->timer.t_eat = *(gdt->params + T_EAT) * MILI_TO_MICRO;
	phs->timer.t_slp = *(gdt->params + T_SLP) * MILI_TO_MICRO;
	phs->timer.t_think = phs->timer.t_die / MILI_TO_MICRO;
	phs->state = STARTING;
	phs->signal = &gdt->signal;
	phs->l_start = &gdt->l_start;
	phs->l_log = &gdt->l_log;
	pthread_mutex_init(&phs->fork, NULL);
	pthread_mutex_unlock(&gdt->l_start);
	while(gdt->start) ;
	while(ft_all_lifes(gdt))
		ft_live(phs);
	return (NULL);
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

void	ft_set_lifetime(t_philo *off_phs, t_philo *last_phs)
{
	while (off_phs < last_phs)
	{
		off_phs->timer.l_eat = ft_date_update();
		off_phs++;
	}
}

short	ft_wait_all_init(t_philo *phs, int n_f)
{
	t_philo	*last_phs;
	t_philo	*off_phs;

	last_phs = phs + n_f;
	off_phs = phs;
	while (phs < last_phs)
	{
		if (!phs->signal)
			return (1);
		else if (phs + 1 == last_phs && phs->signal)
		{
			ft_set_lifetime(off_phs, last_phs);
			return (0);
		}
		phs++;
	}
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
	while (ft_wait_all_init(gdt->phs, all)) ;
}

void	ft_join_threads(t_gdata *gdt, int n_f)
{
	while (n_f--)
		pthread_join(*(gdt->id + n_f), NULL);
}

int	main(int argc, char **argv)
{
	t_gdata	gdt;
	int		n_f;
	
	ft_init_args(argc, argv, gdt.params);
	n_f = *(gdt.params + N_PHILO);
	ft_init_gdata(&gdt, n_f);
	ft_create_threads(&gdt, n_f);
	gdt.start = 0; //Set the signal to start the race.
	ft_join_threads(&gdt, n_f);
	/*Cuando todos retornen, flush the memory.*/
	return (0);
}
