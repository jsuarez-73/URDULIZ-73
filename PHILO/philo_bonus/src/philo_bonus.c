/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:17:44 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/24 21:17:53 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_gdata	gdt;
	int		n_f;
	int		status;

	ft_init_args(argc, argv, gdt.params);
	n_f = *(gdt.params + N_PHILO);
	if (!ft_init_gdata(&gdt, n_f))
		exit(-1);
	if (!ft_create_childs(&gdt, n_f))
		ft_exit(&gdt, -1, PARENT);
	pthread_create(&gdt.id_death, NULL, ft_super_death, &gdt);
	while (n_f--)
	{
		waitpid(-1, &status, 0);
		sem_wait(gdt.s_stop);
		if (!status)
			gdt.tphe++;
		else
			gdt.death++;
		sem_post(gdt.s_stop);
	}
	pthread_join(gdt.id_death, NULL);
	ft_exit(&gdt, 0, PARENT);
	return (0);
}
