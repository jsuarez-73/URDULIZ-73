/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_flush_th.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:34:56 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/28 07:18:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_memory_flush(t_gdata *gdt)
{
	t_philo	*phs;

	phs = gdt->phs;
	if (gdt->id)
		free(gdt->id);
	while (phs < gdt->phs + *(gdt->params + N_PHILO))
	{
		pthread_mutex_destroy(&phs->fork);
		phs++;
	}
	if (gdt->phs)
		free(gdt->phs);
	pthread_mutex_destroy(&gdt->l_shared);
}

void	*ft_time_god(void *arg)
{
	t_gdata	*gdt;

	gdt = (t_gdata *)arg;
	while (ft_all_lifes(gdt, gdt->phs))
		usleep(500);
	return (NULL);
}

void	ft_create_threads(t_gdata *gdt, int n_f)
{
	int	all;

	all = n_f;
	while (n_f--)
	{
		if (n_f >= 1)
			(gdt->phs + n_f)->back = (gdt->phs + n_f - 1);
		pthread_create(gdt->id + n_f, NULL, ft_life_philo, gdt);
	}
	while (ft_wait_all_init(gdt, all))
		;
	pthread_create(&gdt->super, NULL, ft_time_god, gdt);
}

void	ft_join_threads(t_gdata *gdt, int n_f)
{
	while (n_f--)
		pthread_join(*(gdt->id + n_f), NULL);
	pthread_join(gdt->super, NULL);
}
