/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:13:37 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/29 19:29:42 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_init_gdata_helper(t_gdata *gdt)
{
	gdt->tphe = 0;
	gdt->death = 0;
	gdt->philo.timer.t_die = *(gdt->params + T_DIE) * MILI_TO_MICRO;
	gdt->philo.timer.t_slp = *(gdt->params + T_SLP) * MILI_TO_MICRO;
	gdt->philo.timer.t_eat = *(gdt->params + T_EAT) * MILI_TO_MICRO;
	gdt->philo.timer.l_eat = 0;
	gdt->philo.ntme = 0;
	gdt->philo.state = WAITING;
	gdt->philo.id = 0;
}

short	ft_init_gdata(t_gdata *gdt, int n_f)
{
	int	flush_mask;

	flush_mask = NO_FLUSH;
	ft_init_gdata_helper(gdt);
	gdt->id = (pid_t *)malloc(sizeof(pid_t) * n_f);
	if (!gdt->id)
		return (0);
	gdt->s_death = (sem_t **)malloc(sizeof(sem_t *) * n_f);
	if (!gdt->s_death)
		return (0);
	gdt->s_names = ft_set_semaphore_names(n_f);
	if (!gdt->s_names)
		return (0);
	flush_mask = ft_open_semaphores(gdt);
	if (flush_mask)
	{
		ft_flush_semaphores(gdt, CLS_UNLINK, flush_mask);
		free(gdt->id);
		free(gdt->s_death);
		free(gdt->s_names);
		return (0);
	}
	return (1);
}
