/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:41:48 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/28 16:21:36 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_2swap(t_push *p)
{
	short	sw_a;
	short	sw_b;

	sw_a = ft_swap_a(p);
	sw_b = ft_swap_b(p);
	if (sw_a && sw_b)
	{
		ft_printf("#%d\tss\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_2rot(t_push *p)
{
	short	rt_a;
	short	rt_b;

	rt_a = ft_rot_a(p);
	rt_b = ft_rot_b(p);
	if (rt_a && rt_b)
	{
		ft_printf("#%d\trr\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_2revrot(t_push *p)
{
	short	rrt_a;
	short	rrt_b;

	rrt_a = ft_revrot_a(p);
	rrt_b = ft_revrot_b(p);
	if (rrt_a && rrt_b)
	{
		ft_printf("#%d\trrr\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_min_rot(t_push *p, t_uns nmv, int (*f)(t_push *))
{
	while (nmv--)
		f(p);
	return (1);
}

void	ft_clean_push(t_push *p)
{
	if (p->s_a)
		free(p->s_a);
	if (p->s_b)
		free(p->s_b);
}

