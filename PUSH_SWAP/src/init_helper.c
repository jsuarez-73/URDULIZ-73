/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:49:03 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 17:21:06 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_init_argv(int argc, char **argv, t_push *p)
{
	if (ft_guard_service(argc, argv))
	{
		p->s_a = (int *) malloc(sizeof(int) * argc);
		if (!p->s_a)
			exit(-1);
		p->s_b = (int *) malloc(sizeof(int) * argc);
		if (!p->s_b)
			exit(-1);
		ft_init_push(argc, argv, p);
	}
	else
	{
		write(STD_ERR, "Error\n", 6);
		exit(-1);
	}
}

int	ft_arr_len(char **av)
{
	int	cn;

	cn = 0;
	if (av)
	{
		while (*av++)
			cn++;
	}
	return (cn);
}

void	ft_free_argv(char **av)
{
	char	**tmp;

	tmp = av;
	if (av)
	{
		while (*av)
			free(*av++);
		free(tmp);
	}
}
