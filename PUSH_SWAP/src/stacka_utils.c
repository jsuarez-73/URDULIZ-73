/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacka_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:46:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/28 20:54:02 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap_a(t_push *p)
{
	int		tmp;

	if (p->id_a < p->n - 1)
	{
		tmp = *(p->s_a + p->id_a);
		*(p->s_a + p->id_a) = *(p->s_a + p->id_a + 1);
		*(p->s_a + p->id_a + 1) = tmp;
		ft_printf("#%d\tsa\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	else
		return (0);
}

int	ft_push_a(t_push *p)
{
	if (p->id_b < p->n)
	{
		p->id_a--;
		*(p->s_a + p->id_a) = *(p->s_b + p->id_b);
		*(p->s_b + p->id_b) = NN;
		p->n_a++;
		p->id_b++;
		p->n_b--;
		ft_printf("#%d\tpa\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

int	ft_rot_a(t_push *p)
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
		ft_printf("#%d\tra\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

int	ft_revrot_a(t_push *p)
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
		ft_printf("#%d\trra\n", p->mov_n++);
		// ft_show_stacks(p);
		return (1);
	}
	return (0);
}

