/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:31:11 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/28 16:18:43 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_restart_availability(t_gdata *gdt)
{
	int		n_f;
	t_philo	*last;

	n_f = *(gdt->params + N_PHILO);
	last = gdt->phs + n_f - 1;
	if (gdt->phs_feed >= n_f)
	{
		while (n_f >= 1)
		{
			if (last->timer.l_eat > (gdt->phs + n_f - 1)->timer.l_eat)
				last = gdt->phs + n_f - 1;
			n_f--;
		}
		last->feed = 0;
	}
}

static void	ft_update_philo_resources(t_gdata *gdt, t_philo *phs)
{
	pthread_mutex_lock(phs->l_shared);
	phs->ntme++;
	gdt->phs_feed++;
	(*phs->tables)++;
	phs->timer.l_eat = ft_date_update();
	ft_restart_availability(gdt);
	pthread_mutex_unlock(phs->l_shared);
}

static void	ft_live(t_gdata *gdt, t_philo *phs, int n_f)
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
		phs->feed = 1;
		ft_update_philo_resources(gdt, phs);
		ft_push_log(phs, "is eating", EATING);
		ft_usleep(phs->timer.t_eat);
		pthread_mutex_unlock(l_first);
		pthread_mutex_unlock(l_second);
		ft_push_log(phs, "is sleeping", SLEEPING);
		ft_usleep(phs->timer.t_slp);
		ft_push_log(phs, "is thinking", THINKING);
	}
	else
		pthread_mutex_unlock(l_first);
}

void	ft_trigger_life(t_gdata *gdt, t_philo *phs, short *wait)
{
	pthread_mutex_lock(&gdt->l_shared);
	if (!phs->feed)
	{
		pthread_mutex_unlock(&gdt->l_shared);
		ft_live(gdt, phs, *(gdt->params + N_PHILO));
	}
	else
		pthread_mutex_unlock(&gdt->l_shared);
	pthread_mutex_lock(&gdt->l_shared);
	if (gdt->signal == SIGDIED || gdt->signal == SIGNTME)
		*wait = 1;
	pthread_mutex_unlock(&gdt->l_shared);
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
		pthread_mutex_lock(&gdt->l_shared);
		if (!gdt->start)
			wait = 0;
		pthread_mutex_unlock(&gdt->l_shared);
	}
	if (phs->id % 2 == 0)
		usleep(10);
	while (!wait)
		ft_trigger_life(gdt, phs, &wait);
	return (NULL);
}
