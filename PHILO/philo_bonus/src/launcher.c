/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:17:15 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/24 21:17:32 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

short	ft_create_childs(t_gdata *gdt, int n_f)
{
	pid_t	ppid;
	int		cn;
	int		id;

	cn = -1;
	id = 1;
	while (++cn < n_f)
	{
		ppid = fork();
		if (ppid)
		{
			id++;
			*(gdt->id + cn) = ppid;
		}
		else if (ppid == -1)
			return (0);
		else
			ft_exit(gdt, ft_born_philo(gdt, id), CHILD);
	}
	return (1);
}

void	*ft_super_death(void *arg)
{
	t_gdata	*gdt;
	int		cn;

	gdt = (t_gdata *)arg;
	cn = -1;
	while (1)
	{
		sem_wait(gdt->s_stop);
		if (gdt->death)
		{
			while (++cn < *(gdt->params + N_PHILO))
				kill(*(gdt->id + cn), SIGKILL);
			break ;
		}
		else
		{
			if (gdt->tphe == *(gdt->params + N_PHILO))
				break ;
		}
		sem_post(gdt->s_stop);
		usleep(1);
	}
	sem_post(gdt->s_stop);
	return (NULL);
}
