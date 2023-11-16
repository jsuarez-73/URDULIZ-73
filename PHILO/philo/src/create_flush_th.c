/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_flush_th.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:34:56 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/16 11:58:29 by jsuarez-         ###   ########.fr       */
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
	pthread_mutex_destroy(&gdt->l_start);
	pthread_mutex_destroy(&gdt->l_check);
	pthread_mutex_destroy(&gdt->l_log);
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
	while (ft_wait_all_init(gdt, all))
		;
}

void	ft_join_threads(t_gdata *gdt, int n_f)
{
	while (n_f--)
		pthread_join(*(gdt->id + n_f), NULL);
}
