/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:38 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/16 11:59:17 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_gdata	gdt;
	int		n_f;

	ft_init_args(argc, argv, gdt.params);
	n_f = *(gdt.params + N_PHILO);
	ft_init_gdata(&gdt, n_f);
	ft_create_threads(&gdt, n_f);
	ft_join_threads(&gdt, n_f);
	ft_memory_flush(&gdt);
	return (0);
}
