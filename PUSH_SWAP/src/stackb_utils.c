/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackb_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:25:49 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/28 20:54:15 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap_b(t_push *p)
{
	int		tmp;

	if (p->id_b < p->n - 1)
	{
		tmp = *(p->s_b + p->id_b);
		*(p->s_b + p->id_b) = *(p->s_b + p->id_b + 1);
		*(p->s_b + p->id_b + 1) = tmp;
		ft_printf("#%d\tsb\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	else
		return (0);
}

int	ft_push_b(t_push *p)
{
	if (p->id_a < p->n)
	{
		p->id_b--;
		*(p->s_b + p->id_b) = *(p->s_a + p->id_a);
		*(p->s_a + p->id_a) = NN;
		p->n_a--;
		p->id_a++;
		p->n_b++;
		ft_printf("#%d\tpb\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

int	ft_rot_b(t_push *p)
{
	int		first;
	t_uns	i_b;
	t_uns	n_b;
	t_uns	cn;

	n_b = p->n - p->n_a;
	i_b = p->id_b;
	cn = 0;
	if (i_b < (p->n - 1))
	{
		first = *(p->s_b + i_b);
		while (--n_b)
		{
			*(p->s_b + i_b + cn) = *(p->s_b + i_b + cn + 1);
			cn++;
		}
		*(p->s_b + p->n - 1) = first;
		ft_printf("#%d\trb\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

int	ft_revrot_b(t_push *p)
{
	int		last;
	t_uns	i_b;
	t_uns	n_b;
	t_uns	cn;

	n_b = p->n - p->n_a;
	i_b = p->id_b;
	cn = 1;
	if (i_b < (p->n - 1))
	{
		last = *(p->s_b + p->n - 1);
		while (--n_b)
		{
			*(p->s_b + p->n - cn) = *(p->s_b + p->n - cn - 1);
			cn++;
		}
		*(p->s_b + i_b) = last;
		ft_printf("#%d\trrb\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

