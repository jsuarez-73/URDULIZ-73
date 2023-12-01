/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:10:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/12/01 15:37:55 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_semaphores(t_gdata *gdt, int flush_mask)
{
	if (flush_mask & F_FORK)
		sem_close(gdt->s_fork);
	if (flush_mask & F_DEATH)
		sem_close(gdt->s_death);
	if (flush_mask & F_STOP)
		sem_close(gdt->s_stop);
	if (flush_mask & F_TERM)
		sem_close(gdt->s_term);
	if (flush_mask & F_TABLE)
		sem_close(gdt->s_table);
}

void	ft_unlink_semaphores(int flush_mask)
{
	if (flush_mask & F_FORK)
		sem_unlink(SEM_FORK);
	if (flush_mask & F_DEATH)
		sem_unlink(SEM_DEATH);
	if (flush_mask & F_STOP)
		sem_unlink(SEM_STOP);
	if (flush_mask & F_TERM)
		sem_unlink(SEM_TERM);
	if (flush_mask & F_TABLE)
		sem_unlink(SEM_TABLE);
}

void	ft_flush_semaphores(t_gdata *gdt, int cls_mask, int flush_mask)
{
	if (flush_mask & FE_NFLUSH)
		return ;
	if (cls_mask & CLOSE)
		ft_close_semaphores(gdt, flush_mask);
	if (cls_mask & UNLINK)
		ft_unlink_semaphores(flush_mask);
}

int	ft_open_semaphores(t_gdata *gdt)
{
	int	o_flags;
	int	n_f;

	o_flags = O_CREAT | O_EXCL;
	n_f = *(gdt->params + N_PHILO);
	ft_unlink_semaphores(FLUSH_ALL);
	gdt->s_fork = sem_open(SEM_FORK, o_flags, 0664, n_f);
	if (gdt->s_fork == SEM_FAILED)
		return (FE_NFLUSH);
	gdt->s_death = sem_open(SEM_DEATH, o_flags, 0664, 1);
	if (gdt->s_death == SEM_FAILED)
		return (F_FORK);
	gdt->s_stop = sem_open(SEM_STOP, o_flags, 0664, 1);
	if (gdt->s_stop == SEM_FAILED)
		return (F_FORK | F_DEATH);
	gdt->s_term = sem_open(SEM_TERM, o_flags, 0664, 1);
	if (gdt->s_term == SEM_FAILED)
		return (F_FORK | F_DEATH | F_STOP);
	gdt->s_table = sem_open(SEM_TABLE, o_flags, 0664, n_f / 2);
	if (gdt->s_table == SEM_FAILED)
		return (F_FORK | F_DEATH | F_STOP | F_TERM);
	return (NO_FLUSH);
}
