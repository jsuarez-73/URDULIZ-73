/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:31:11 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/28 07:53:59 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(long ms)
{
	struct timeval	tday;
	long			start;
	long			now;

	gettimeofday(&tday, NULL);
	start = tday.tv_sec * 1000 + tday.tv_usec / 1000;
	now = start;
	while ((now - start) <= (ms / 1000))
	{
		usleep(500);
		gettimeofday(&tday, NULL);
		now = tday.tv_sec * 1000 + tday.tv_usec / 1000;
	}
}

static short	ft_everyone_has_eaten(t_gdata *gdt, int n_f)
{
	t_philo	*p;

	p = gdt->phs;
	while (n_f--)
	{
		if ((p + n_f)->ntme == *(gdt->params + N_EPME) && !(p + n_f)->ticked)
		{
			(p + n_f)->ticked = 1;
			gdt->tphe++;
		}
		if (gdt->tphe == *(gdt->params + N_PHILO))
		{
			gdt->signal = SIGNTME;
			return (1);
		}
	}
	return (0);
}

static t_philo	*ft_someone_has_death(t_philo *phs, t_philo *last_phs)
{
	long	now;
	long	delta_time;

	while (phs < last_phs)
	{
		now = ft_date_update();
		delta_time = (now - phs->timer.l_eat) * MILI_TO_MICRO;
		if (delta_time >= phs->timer.t_die)
			return (phs);
		phs++;
	}
	return (NULL);
}

short	ft_all_lifes(t_gdata *gdt, t_philo *phs)
{
	long	now;
	t_philo	*died;

	pthread_mutex_lock(&gdt->l_shared);
	died = ft_someone_has_death(phs, gdt->phs + *(gdt->params + N_PHILO));
	if (died)
	{
		gdt->signal = SIGDIED;
		now = ft_date_update();
		printf("%ld %u %s %s\n", now, died->id, "has died", HEADSTONE);
		pthread_mutex_unlock(&gdt->l_shared);
		return (0);
	}
	if (*(gdt->params + N_EPME))
	{
		if (ft_everyone_has_eaten(gdt, *(gdt->params + N_PHILO)))
		{
			pthread_mutex_unlock(&gdt->l_shared);
			return (0);
		}
	}
	pthread_mutex_unlock(&gdt->l_shared);
	return (1);
}

// static int	ft_check_availability(t_gdata *gdt, t_philo *phs)
// {
// 	pthread_mutex_lock(&gdt->l_shared);
// 	if (gdt->tables > 0 && !phs->feed)
// 	{
// 		gdt->tables--;
// 		pthread_mutex_unlock(&gdt->l_shared);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&gdt->l_shared);
// 	return (0);
// }

t_philo	*ft_last_feed(t_gdata *gdt)
{
	int		n_f;
	t_philo	*last;

	n_f = *(gdt->params + N_PHILO);
	last = gdt->phs + n_f - 1;
	while (n_f >= 1)
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

	n_f = *(gdt->params + N_PHILO);
	if (gdt->phs_feed >= n_f)
	{
		last_feed = ft_last_feed(gdt);
		last_feed->feed = 0;
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
	if (n_f >= 1)
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
		// usleep(phs->timer.t_think);
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
		pthread_mutex_lock(&gdt->l_shared);
		if (!gdt->start)
			wait = 0;
		pthread_mutex_unlock(&gdt->l_shared);
	}
	if (phs->id % 2 == 0)
		usleep(10);
	while (!wait)
	{
		if (!phs->feed)
			ft_live(gdt, phs, *(gdt->params + N_PHILO));
		pthread_mutex_lock(&gdt->l_shared);
		if (gdt->signal == SIGDIED || gdt->signal == SIGNTME)
			wait = 1;
		pthread_mutex_unlock(&gdt->l_shared);
	}
	return (NULL);
}
