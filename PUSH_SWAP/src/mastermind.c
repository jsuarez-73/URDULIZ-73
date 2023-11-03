/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mastermind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:08:59 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/01 20:23:49 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_calc_min(t_push *p, int t_st, t_idtm *idtm)
{
	t_uns	cn;
	int		cst;
	t_uns	nx_id;

	cn = p->n;
	if (t_st == STACK_A)
	{
		while (cn-- > p->id_a)
		{
			nx_id = ft_next_down(p->s_b, *(p->s_a + cn), p->n, p->id_b);
			cst = ft_ova_cost(p, cn, nx_id);
			ft_min_cost(cst, idtm, cn, nx_id);
		}
	}
	else if (t_st == STACK_B)
	{
		while (cn-- > p->id_b)
		{
			nx_id = ft_next_up(p->s_a, *(p->s_b + cn), p->n, p->id_a);
			cst = ft_ova_cost(p, nx_id, cn);
			ft_min_cost(cst, idtm, nx_id, cn);
		}
	}
}

static void	ft_min_pushb(t_push *p)
{
	t_idtm	idtm;

	idtm.m_cst = NN;
	if (p->n_b < 2)
		ft_push_b(p, NO_QUIET);
	else
	{
		ft_calc_min(p, STACK_A, &idtm);
		if (idtm.m_cst != NN)
		{
			ft_rot_stacks(p, &idtm);
			ft_push_b(p, NO_QUIET);
		}
	}
}

static void	ft_min_pusha(t_push *p)
{
	t_idtm	idtm;

	idtm.m_cst = NN;
	if (p->n_b > 0)
	{
		ft_calc_min(p, STACK_B, &idtm);
		if (idtm.m_cst != NN)
		{
			ft_rot_stacks(p, &idtm);
			ft_push_a(p, NO_QUIET);
		}
	}
}

static void	ft_last_sort(t_push *p)
{
	int	min;

	min = ft_min(p->s_a, p->n, p->id_a);
	if (min)
	{
		if ((min - p->id_a) > (p->n - min))
			ft_min_rot(p, p->n - min, ft_revrot_a, NO_QUIET);
		else
			ft_min_rot(p, min - p->id_a, ft_rot_a, NO_QUIET);
	}
}

void	ft_think(t_push *p)
{
	if (p->pshb && p->n_a > 3)
	{
		ft_min_pushb(p);
		if (p->n_a == 3)
		{
			p->pshb = 0;
			ft_sort(p);
		}
	}
	else if (!p->pshb)
	{
		ft_min_pusha(p);
		if (p->n_a == p->n)
			ft_last_sort(p);
	}
}
