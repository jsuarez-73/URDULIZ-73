/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:17:15 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/17 10:13:24 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_init_push(int argc, char **argv, t_push *push)
{
	int	cntr;

	cntr = 0;
	if (argc > 1)
	{
		push->elem = --argc;
		push->stack_a = (int *) malloc(sizeof(int) * argc);
		if (!push->stack_a)
			exit(-1);
		push->stack_b = (int *) malloc(sizeof(int) * argc);
		if (!push->stack_b)
			exit(-1);
		while (argc--)
			*(push->stack_a + cntr++) = ft_atoi(*(++argv));
		push->elem_a = push->elem;
	}
	else
		exit (0);
}

int	main(int argc, char **argv)
{
	t_push	push;

	ft_init_push(argc, argv, &push);
	return (0);
}