/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:41:48 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/31 19:38:14 by jsuarez-         ###   ########.fr       */
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

void	ft_sort(t_push *p)
{
	t_uns	big;

	big = ft_id_big(p->s_a, p->id_a, p->n - 1);
	if (big == p->n - 3)
		ft_rot_a(p, NO_QUIET);
	else if (big == p->n - 2)
		ft_revrot_a(p, NO_QUIET);
	if (*(p->s_a + p->id_a) > *(p->s_a + p->id_a + 1))
		ft_swap_a(p, NO_QUIET);
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

void	ft_show_stacks(t_push *p)
{
	t_uns	elem_n;
	t_uns	idx_a;
	t_uns	idx_b;
	t_uns	c;

	elem_n = p->n;
	idx_b = p->n_a;
	idx_a = p->n - p->n_a;
	c = 0;
	ft_printf("STACKS\nidx\tstack A\tstackB\n");
	while (elem_n--)
	{
		if (c >= idx_b && c >= idx_a)
			ft_printf("%u\t%d\t%d\n", c, *(p->s_a + c), *(p->s_b + c));
		else if (c >= idx_b && c < idx_a)
			ft_printf("%u\tX\t%d\n", c, *(p->s_b + c));
		else if (c < idx_b && c >= idx_a)
			ft_printf("%u\t%d\tX\n", c, *(p->s_a + c));
		else
			ft_printf("%u\tX\tX\n", c);
		c++;
	}
	ft_printf("\n");
}
