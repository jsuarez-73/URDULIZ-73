/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:31:11 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/15 19:40:08 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_live(t_philo *phs, int n_f)
{
	pthread_mutex_t	*l_first;
	pthread_mutex_t	*l_second;

	ft_set_locks(phs, &l_first, &l_second);
	pthread_mutex_lock(l_first);
	if (n_f > 1)
	{
		ft_push_log(phs, "has taken a fork", FORKING_ONE);
		pthread_mutex_lock(l_second);
		ft_push_log(phs, "has taken a fork", FORKING_TWO);
		phs->timer.l_eat = ft_date_update();
		ft_push_log(phs, "is eating", EATING);
		usleep(phs->timer.t_eat);
		phs->ntme++; 
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

static short	ft_everyone_has_eaten(t_gdata *gdt, t_philo *phs)
{
	if (phs->ntme == *(gdt->params + N_EPME) && !phs->ticked)
	{
		phs->ticked = 1;
		gdt->tphe++;
		pthread_mutex_lock(&gdt->l_log);
		gdt->signal = SIGNTME;
		pthread_mutex_unlock(&gdt->l_log);
	}
	if (gdt->tphe == *(gdt->params + N_PHILO))
		return (1);
	return (0);
}

static short	ft_someone_has_death(t_philo *phs, suseconds_t delta_time)
{
	pthread_mutex_lock(phs->l_log);
	if (*phs->signal != SIGCONT)
	{
		pthread_mutex_unlock(phs->l_log);
		return (1);
	}
	if (delta_time >= phs->timer.t_die)
	{
		pthread_mutex_unlock(phs->l_log);
		ft_push_log(phs, "died", DIED);
		return (1);
	}
	pthread_mutex_unlock(phs->l_log);
	return (0);
}
static short	ft_all_lifes(t_gdata *gdt, t_philo *phs)
{
	suseconds_t	now;
	suseconds_t	delta_time;

	pthread_mutex_lock(&gdt->l_check);
	now = ft_date_update();
	delta_time = (now - phs->timer.l_eat) * MILI_TO_MICRO;
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
		ft_live(phs, *(gdt->params + N_PHILO));
	return (NULL);
}
