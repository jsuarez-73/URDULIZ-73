/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:24:11 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/30 19:16:43 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

typedef	struct	s_gdt
{
	sem_t	*sem;
	sem_t	*term;
	int		shared;
}	t_gdt;

void	ft_child_execution(t_gdt *gdt)
{
	int	cn;

	cn = 1000;
	while (cn--)
	{
		sem_wait(gdt->sem);
		printf("Llega: %d\n", getpid());
		sem_post(gdt->sem);

		sem_wait(gdt->sem);
		gdt->shared = gdt->shared * 7 - 1;
		printf("Inside %d\n", getpid());
		usleep(1);
		sem_post(gdt->sem);

		sem_wait(gdt->sem);
		printf("Outside: %d\n", getpid());
		sem_post(gdt->sem);
	}
	exit(0);
}

int	main(void)
{
	pid_t	pid;
	t_gdt	gdata;
	int		cn;
	int		status;
	

	cn = 10;
	gdata.sem = sem_open(SEM_TABLE, O_CREAT, 0664, 1);
	gdata.term = sem_open(SEM_TERM, O_CREAT, 0664, 1);
	gdata.shared = 73;
	printf("Parent id: %d\n", getpid());
	while (cn--)
	{
		pid = fork();
		if (!pid)
			ft_child_execution(&gdata);
	}
	cn = 10;
	while (cn--)
	{
		waitpid(-1, &status, 0);
		// sem_wait(gdata.sem);
		// printf("Padre:%d\tStatus: %d\n",getpid(), status);
		// sem_post(gdata.sem);
	}
	sem_close(gdata.sem);
	sem_close(gdata.term);
	sem_unlink(SEM_TABLE);
	sem_unlink(SEM_TERM);
	return (0);
}