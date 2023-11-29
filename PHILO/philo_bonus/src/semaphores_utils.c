/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:10:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/29 19:30:29 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_semaphores(t_gdata *gdt, int flush_mask)
{
	int	cn;

	cn = *(gdt->params + N_PHILO);
	if (flush_mask & F_FORK)
		sem_close(gdt->s_fork);
	if (flush_mask & F_DEATH)
	{
		while (cn--)
			sem_close(*(gdt->s_death + cn));
	}
	if (flush_mask & F_STOP)
		sem_close(gdt->s_stop);
	if (flush_mask & F_TERM)
		sem_close(gdt->s_term);
	if (flush_mask & F_TABLE)
		sem_close(gdt->s_table);
}

void	ft_unlink_semaphores(t_gdata *gdt, int flush_mask)
{
	int	cn;
	int	res;

	cn = *(gdt->params + N_PHILO);
	res = 0;
	if (flush_mask & F_FORK)
		sem_unlink(SEM_FORK);
	if (flush_mask & F_DEATH)
		while (cn-- && res == 0)
			res = sem_unlink(*(gdt->s_names + cn));
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
		ft_unlink_semaphores(gdt, flush_mask);
}

short	ft_open_sdeaths(t_gdata *gdt)
{
	int		cn;
	int		o_flgs;

	cn = *(gdt->params + N_PHILO);
	o_flgs = O_CREAT | O_EXCL;
	while (cn--)
	{
		*(gdt->s_death + cn) = sem_open(*(gdt->s_names + cn), o_flgs, 0664, 1);
		if (*(gdt->s_death + cn) == SEM_FAILED)
		{
			while (++cn < *(gdt->params + N_PHILO))
			{
				sem_close(*(gdt->s_death + cn));
				sem_unlink(*(gdt->s_names + cn));
			}
			return (0);
		}
	}
	return (1);
}

int	ft_open_semaphores(t_gdata *gdt)
{
	int	o_flags;
	int	cn;
	int	n_f;

	cn = *(gdt->params + N_PHILO);
	n_f = cn;
	o_flags = O_CREAT | O_EXCL;
	ft_unlink_semaphores(gdt, FLUSH_ALL);
	gdt->s_fork = sem_open(SEM_FORK, o_flags, 0664, n_f);
	if (gdt->s_fork == SEM_FAILED)
		return (FE_NFLUSH);
	if (!ft_open_sdeaths(gdt))
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
