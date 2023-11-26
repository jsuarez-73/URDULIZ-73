/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:31:11 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/25 20:33:23 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	ft_everyone_has_eaten(t_gdata *gdt, t_philo *phs)
{
	pthread_mutex_lock(&gdt->l_log);
	if (phs->ntme == *(gdt->params + N_EPME) && !phs->ticked)
	{
		phs->ticked = 1;
		gdt->tphe++;
		gdt->signal = SIGNTME;
	}
	if (gdt->tphe == *(gdt->params + N_PHILO))
	{
		pthread_mutex_unlock(&gdt->l_log);
		return (1);
	}
	pthread_mutex_unlock(&gdt->l_log);
	return (0);
}

static short	ft_someone_has_death(t_philo *phs, t_philo *last_phs)
{
	long	now;
	long	delta_time;

	while (phs < last_phs)
	{
		pthread_mutex_lock(phs->l_log);
		now = ft_date_update();
		delta_time = (now - phs->timer.l_eat) * MILI_TO_MICRO;
		if (*phs->signal == SIGDIED || delta_time >= phs->timer.t_die)
		{
			pthread_mutex_unlock(phs->l_log);
			return (1);
		}
		pthread_mutex_unlock(phs->l_log);
		phs++;
	}
	return (0);
}

short	ft_all_lifes(t_gdata *gdt, t_philo *phs)
{
	pthread_mutex_lock(&gdt->l_check);
	if (ft_someone_has_death(phs, gdt->phs + *(gdt->params + N_PHILO)))
	{
		ft_push_log(phs, "died", DIED);
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

static int	ft_check_availability(t_gdata *gdt, t_philo *phs)
{
	pthread_mutex_lock(&gdt->l_avail);
	if (gdt->tables > 0 && !phs->feed)
	{
		gdt->tables--;
		pthread_mutex_unlock(&gdt->l_avail);
		return (1);
	}
	pthread_mutex_unlock(&gdt->l_avail);
	return (0);
}

t_philo	*ft_last_feed(t_gdata *gdt)
{
	int		n_f;
	t_philo	*last;

	n_f = *(gdt->params + N_PHILO);
	last = gdt->phs + n_f - 1;
	while (n_f > 1)
	{
		if (last->timer.l_eat > (gdt->phs + n_f - 1)->timer.l_eat)
			last = gdt->phs + n_f - 1;
		n_f--;
	}
	return (last);
}

void	ft_restart_availability(t_gdata *gdt)
{
	int		n_f;
	t_philo	*last_feed;

	pthread_mutex_lock(&gdt->l_avail);
	n_f = *(gdt->params + N_PHILO);
	if (gdt->phs_feed >= n_f)
	{
		last_feed = ft_last_feed(gdt);
		last_feed->feed = 0;
	}
	pthread_mutex_unlock(&gdt->l_avail);
}

static void	ft_push_availability(int *tables, pthread_mutex_t *l_avail)
{
	pthread_mutex_lock(l_avail);
	(*tables)++;
	pthread_mutex_unlock(l_avail);
	usleep(1);
}
/*RESTAR_AVAILABILITY ESTA EN UNA UBICACION CONTRAPRODUCENTE, DICHA ACTUALIZA
CION DE FUNCION NO DEBE ESPERAR QUE UN PHILOSOPHO ACTUALICE DICHO PARAMETRO
PODRIA TARDAR INTERVALOS DE 200us con lo cual debemos ponerlos en el hilo
supervisor.*/
static void	ft_live(t_gdata *gdt, t_philo *phs, int n_f)
{
	pthread_mutex_t	*l_first;
	pthread_mutex_t	*l_second;

	ft_set_locks(phs, &l_first, &l_second);
	pthread_mutex_lock(l_first);
	if (n_f >= 1)
	{
		ft_push_log(phs, "has taken a fork", FORKING_ONE);
		pthread_mutex_lock(l_second);
		ft_push_log(phs, "has taken a fork", FORKING_TWO);
		pthread_mutex_lock(phs->l_log);
		phs->feed = 1;
		phs->timer.l_eat = ft_date_update();
		phs->ntme++;
		gdt->phs_feed++;
		ft_push_availability(phs->tables, phs->l_avail);
		ft_restart_availability(gdt);
		pthread_mutex_unlock(phs->l_log);
		ft_push_log(phs, "is eating", EATING);
		usleep(phs->timer.t_eat);
		pthread_mutex_unlock(l_first);
		pthread_mutex_unlock(l_second);
		ft_push_log(phs, "is sleeping", SLEEPING);
		usleep(phs->timer.t_slp);
		ft_push_log(phs, "is thinking", THINKING);
		usleep(phs->timer.t_think);
	}
	else
		pthread_mutex_unlock(l_first);
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
	while (ft_all_lifes(gdt, phs))
	{
		if (ft_check_availability(gdt, phs))
			ft_live(gdt, phs, *(gdt->params + N_PHILO));
	}
	return (NULL);
}
