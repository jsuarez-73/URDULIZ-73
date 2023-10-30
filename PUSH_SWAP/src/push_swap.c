/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:17:15 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/30 18:49:41 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_push	p;

	ft_check_args(argc, argv, &p);
	if (p.n == 2)
	{
		if (*p.s_a > *(p.s_a + 1))
			ft_swap_a(&p, NO_QUIET);
	}
	else if (p.n_a == 3)
		ft_sort(&p);
	else
	{
		while (!ft_is_ordered(&p) || p.id_b < p.n)
		{
			ft_think(&p);
		}
	}
	ft_clean_push(&p);
	exit(0);
}
