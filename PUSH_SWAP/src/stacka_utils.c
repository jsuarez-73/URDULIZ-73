/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacka_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:46:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/02 23:56:57 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap_a(t_push *p, int vrbose)
{
	int		tmp;

	if (p->id_a < p->n - 1)
	{
		tmp = *(p->s_a + p->id_a);
		*(p->s_a + p->id_a) = *(p->s_a + p->id_a + 1);
		*(p->s_a + p->id_a + 1) = tmp;
		if (vrbose)
			ft_printf("sa\n", p->mov_n++);
		return (1);
	}
	else
		return (0);
}

int	ft_push_a(t_push *p, int vrbose)
{
	if (p->id_b < p->n)
	{
		p->id_a--;
		*(p->s_a + p->id_a) = *(p->s_b + p->id_b);
		*(p->s_b + p->id_b) = NN;
		p->n_a++;
		p->id_b++;
		p->n_b--;
		if (vrbose)
			ft_printf("pa\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_rot_a(t_push *p, int vrbose)
{
	int		first;
	t_uns	i_a;
	t_uns	n_a;
	t_uns	cn;

	n_a = p->n_a;
	i_a = p->id_a;
	cn = 0;
	if (i_a < (p->n - 1))
	{
		first = *(p->s_a + i_a);
		while (--n_a)
		{
			*(p->s_a + i_a + cn) = *(p->s_a + i_a + cn + 1);
			cn++;
		}
		*(p->s_a + p->n - 1) = first;
		if (vrbose)
			ft_printf("ra\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_revrot_a(t_push *p, int vrbose)
{
	int		last;
	t_uns	i_a;
	t_uns	n_a;
	t_uns	cn;

	n_a = p->n_a;
	i_a = p->id_a;
	cn = 1;
	if (i_a < (p->n - 1))
	{
		last = *(p->s_a + p->n - 1);
		while (--n_a)
		{
			*(p->s_a + p->n - cn) = *(p->s_a + p->n - cn - 1);
			cn++;
		}
		*(p->s_a + i_a) = last;
		if (vrbose)
			ft_printf("rra\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_2revrot(t_push *p, int vrbose)
{
	short	rrt_a;
	short	rrt_b;

	rrt_a = ft_revrot_a(p, QUIET);
	rrt_b = ft_revrot_b(p, QUIET);
	if (rrt_a && rrt_b)
	{
		if (vrbose)
			ft_printf("rrr\n", p->mov_n++);
		return (1);
	}
	return (0);
}
