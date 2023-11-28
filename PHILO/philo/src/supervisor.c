/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:12:28 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/28 16:13:07 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
