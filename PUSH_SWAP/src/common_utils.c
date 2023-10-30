/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:41:48 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/30 21:21:57 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_2swap(t_push *p, int vrbose)
{
	short	sw_a;
	short	sw_b;

	sw_a = ft_swap_a(p, vrbose);
	sw_b = ft_swap_b(p, vrbose);
	if (sw_a && sw_b)
	{
		ft_printf("ss\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_2rot(t_push *p, int vrbose)
{
	short	rt_a;
	short	rt_b;

	rt_a = ft_rot_a(p, vrbose);
	rt_b = ft_rot_b(p, vrbose);
	if (rt_a && rt_b)
	{
		ft_printf("rr\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_2revrot(t_push *p, int vrbose)
{
	short	rrt_a;
	short	rrt_b;

	rrt_a = ft_revrot_a(p, vrbose);
	rrt_b = ft_revrot_b(p, vrbose);
	if (rrt_a && rrt_b)
	{
		ft_printf("rrr\n", p->mov_n++);
		return (1);
	}
	return (0);
}

int	ft_min_rot(t_push *p, t_uns nmv, int (*f)(t_push *, int), int vrbose)
{
	while (nmv--)
		f(p, vrbose);
	return (1);
}

void	ft_clean_push(t_push *p)
{
	if (p->s_a)
		free(p->s_a);
	if (p->s_b)
		free(p->s_b);
}
