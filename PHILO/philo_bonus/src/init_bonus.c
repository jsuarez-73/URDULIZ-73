/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:37 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/12/01 15:30:53 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

short	ft_init_gdata(t_gdata *gdt, int n_f)
{
	int	flush_mask;

	flush_mask = NO_FLUSH;
	gdt->tphe = 0;
	gdt->death = 0;
	gdt->philo.timer.t_die = *(gdt->params + T_DIE) * MILI_TO_MICRO;
	gdt->philo.timer.t_slp = *(gdt->params + T_SLP) * MILI_TO_MICRO;
	gdt->philo.timer.t_eat = *(gdt->params + T_EAT) * MILI_TO_MICRO;
	gdt->philo.timer.l_eat = 0;
	gdt->philo.ntme = 0;
	gdt->philo.state = WAITING;
	gdt->philo.id = 0;
	gdt->id = (pid_t *)malloc(sizeof(pid_t) * n_f);
	if (!gdt->id)
		return (0);
	flush_mask = ft_open_semaphores(gdt);
	if (flush_mask)
	{
		ft_flush_semaphores(gdt, CLS_UNLINK, flush_mask);
		free(gdt->id);
		return (0);
	}
	return (1);
}
