/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desicion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:37:02 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/02 23:59:15 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_cost(t_uns id_s, t_uns f_ids, t_uns n)
{
	t_uns	cst;

	cst = NN;
	if (id_s < f_ids || id_s >= n)
		return (cst);
	if ((id_s - f_ids) > (n - id_s))
		cst = -(n - id_s);
	else
		cst = id_s - f_ids;
	return (cst);
}

int	ft_ova_cost(t_push *p, t_uns id_a, t_uns id_b)
{
	int	cst_a;
	int	cst_b;

	cst_a = ft_cost(id_a, p->id_a, p->n);
	cst_b = ft_cost(id_b, p->id_b, p->n);
	if (cst_a < 0 && cst_b < 0)
		return ((-cst_a) * (cst_a <= cst_b) + (-cst_b) * (cst_b < cst_a));
	else if (cst_a > 0 && cst_b > 0)
		return ((cst_a) * (cst_a >= cst_b) + (cst_b) * (cst_b > cst_a));
	else
	{
		if (cst_a < 0)
			cst_a *= -1;
		else if (cst_b < 0)
			cst_b *= -1;
	}
	if (cst_b == NN || cst_a == NN)
		return (NN);
	return (cst_a + cst_b);
}

void	ft_min_cost(int cst, t_idtm *idtm, t_uns id_a, t_uns id_b)
{
	if (idtm->m_cst == -1)
	{
		idtm->m_cst = cst;
		idtm->id_a = id_a;
		idtm->id_b = id_b;
	}
	else if (cst <= idtm->m_cst)
	{
		idtm->m_cst = cst;
		idtm->id_a = id_a;
		idtm->id_b = id_b;
	}
}

void	ft_2min_rot(t_push *p, t_idtm *idtm, int lmda)
{
	int	diff_ab;
	int	diff_ba;

	diff_ab = idtm->id_a - p->id_a - (idtm->id_b - p->id_b);
	diff_ba = idtm->id_b - p->id_b - (idtm->id_a - p->id_a);
	if (idtm->id_a >= idtm->id_b && lmda)
	{
		ft_min_rot(p, p->n - idtm->id_a, ft_2revrot, NO_QUIET);
		ft_min_rot(p, idtm->id_a - idtm->id_b, ft_revrot_b, NO_QUIET);
	}
	else if (lmda)
	{
		ft_min_rot(p, p->n - idtm->id_b, ft_2revrot, NO_QUIET);
		ft_min_rot(p, idtm->id_b - idtm->id_a, ft_revrot_a, NO_QUIET);
	}
	if ((idtm->id_a - p->id_a) >= (idtm->id_b - p->id_b) && !lmda)
	{
		ft_min_rot(p, idtm->id_b - p->id_b, ft_2rot, NO_QUIET);
		ft_min_rot(p, diff_ab, ft_rot_a, NO_QUIET);
	}
	else if (!lmda)
	{
		ft_min_rot(p, idtm->id_a - p->id_a, ft_2rot, NO_QUIET);
		ft_min_rot(p, diff_ba, ft_rot_b, NO_QUIET);
	}
}

void	ft_rot_stacks(t_push *p, t_idtm *idtm)
{
	int	lmda;
	int	eps;

	lmda = (idtm->id_a - p->id_a) > (p->n - idtm->id_a);
	eps = (idtm->id_b - p->id_b) > (p->n - idtm->id_b);
	if (lmda == eps)
		ft_2min_rot(p, idtm, lmda);
	else if (lmda && !eps)
	{
		ft_min_rot(p, p->n - idtm->id_a, ft_revrot_a, NO_QUIET);
		ft_min_rot(p, idtm->id_b - p->id_b, ft_rot_b, NO_QUIET);
	}
	else if (!lmda && eps)
	{
		ft_min_rot(p, idtm->id_a - p->id_a, ft_rot_a, NO_QUIET);
		ft_min_rot(p, p->n - idtm->id_b, ft_revrot_b, NO_QUIET);
	}	
}
