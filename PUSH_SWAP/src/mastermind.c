/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mastermind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:08:59 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/29 12:44:33 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
t_uns	ft_id_big(int *st, t_uns f_id, t_uns n_id)
{
	t_uns	big;


	big = 2;
	while (n_id > f_id)
	{
		if (*(st + n_id) < *(st + n_id - 1))
			big--;
		n_id--;
	}
	return (big);
}

void	ft_sort(t_push *p)
{
	t_uns	big;

	big = ft_id_big(p->s_a, p->id_a, p->n - 1);
	if (big == 0)
		ft_rot_a(p, NO_QUIET);
	else if (big == 1)
		ft_revrot_a(p, NO_QUIET);
	if (*(p->s_a + p->id_a) > *(p->s_a +p->id_a + 1))
		ft_swap_a(p);
}
/*m = p->n, f_id = p->id_b*/
int	ft_max(int *st, t_uns m, t_uns f_id)
{
	int	max;
	int	b_id;

	max = *(st + m - 1);
	b_id = m - 1;
	while (m-- > (f_id + 1))
	{
		if (max < *(st + m - 1))
		{
			max = *(st + m - 1);
			b_id = m - 1;
		}
	}
	return (b_id);
}

t_uns	ft_next_down(int *st, int num, t_uns n, t_uns f_id)
{
	int		dlt;
	int		m_dlt;
	t_uns	nxtd;
	t_uns	m;

	nxtd = NN;
	m_dlt = NN;
	m = n;
	while (n-- > f_id)
	{
		dlt = num - *(st + n);
		if (dlt > 0 && (m_dlt > dlt || m_dlt == NN))
		{
			m_dlt = dlt;
			nxtd = n;
		}
	}
	if (m_dlt == NN)
		return (ft_max(st, m, f_id));
	return (nxtd);
}

int	ft_min(int *st, t_uns m, t_uns f_id)
{
	int	min;
	int	s_id;

	min = *(st + m - 1);
	s_id = m - 1;
	while (m-- > (f_id + 1))
	{
		if (min > *(st + m - 1))
		{
			min = *(st + m - 1);
			s_id = m - 1;
		}
	}
	return (s_id);
}

t_uns	ft_next_up(int *st, int num, t_uns n, t_uns f_id)
{
	int		dlt;
	int		b_dlt;
	t_uns	nxtu;
	t_uns	m;

	nxtu = NN;
	b_dlt = NN;
	m = n;
	while (n-- > f_id)
	{
		dlt = num - *(st + n);
		if (dlt < 0 && (b_dlt < dlt || b_dlt == NN))
		{
			b_dlt = dlt;
			nxtu = n;
		}
	}
	if (b_dlt == NN)
		return (ft_min(st, m, f_id));
	return (nxtu);
}
int	ft_cost(t_uns id_s, t_uns f_ids, t_uns n)
{
	t_uns	cst;

	cst = -1;
	if (id_s < f_ids || id_s >= n)
		return (cst);
	if ((id_s - f_ids) > (n - id_s))
		cst = n - id_s;
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
	if (cst_b == -1 || cst_a == -1)
		return (-1);
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
	else if (cst < idtm->m_cst)
	{
		idtm->m_cst = cst;
		idtm->id_a = id_a;
		idtm->id_b = id_b;
	}
}

void	ft_calc_min(t_push *p, int t_st, t_idtm *idtm)
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
void	ft_2min_rot(t_push *p, t_idtm *idtm, int lmda)
{
	if (lmda)
	{
		if (idtm->id_a >= idtm->id_b)
		{
			ft_min_rot(p, p->n - idtm->id_a, ft_2revrot, QUIET);
			ft_min_rot(p, idtm->id_a - idtm->id_b, ft_revrot_b, NO_QUIET);
		}
		else
		{
			ft_min_rot(p, p->n - idtm->id_b, ft_2revrot, QUIET);
			ft_min_rot(p, idtm->id_b - idtm->id_a, ft_revrot_a, NO_QUIET);			
		}
	}
	else
	{
		if ((idtm->id_a - p->id_a) >= (idtm->id_b - p->id_b))
		{
			ft_min_rot(p, idtm->id_b - p->id_b, ft_2rot, QUIET);
			ft_min_rot(p, idtm->id_a - p->id_a - (idtm->id_b - p->id_b), ft_rot_a, NO_QUIET);
		}
		else
		{
			ft_min_rot(p, idtm->id_a - p->id_a, ft_2rot, QUIET);
			ft_min_rot(p, idtm->id_b - p->id_b - (idtm->id_a - p->id_a), ft_rot_b, NO_QUIET);
		}
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

void	ft_min_pushb(t_push *p)
{
	t_idtm	idtm;

	idtm.m_cst = -1;
	if (p->n_b < 3)
		ft_push_b(p);
	else
	{
		ft_calc_min(p, STACK_A, &idtm);
		if (idtm.m_cst != -1)
		{
			ft_rot_stacks(p, &idtm);
			ft_push_b(p);
		}
	}
}

void	ft_min_pusha(t_push *p)
{
	t_idtm	idtm;

	idtm.m_cst = -1;
	if (p->n_b > 0)
	{
		ft_calc_min(p, STACK_B, &idtm);
		if (idtm.m_cst != -1)
		{
			ft_rot_stacks(p, &idtm);
			ft_push_a(p);
		}
	}
}

void	ft_last_sort(t_push *p)
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
/*500 caracteres funcionando, presenta errores cuando se duplican los valores en la lista.
falta implementar que no permita numeros duplicados.
falta implementar que si se encuentra con movimientos repetidos de ra y rb, generar el
rr, para ahorrar movimientos.*/
void	ft_think(t_push *p)
{
	if (p->n_a == 3 && p->pshb)
		ft_sort(p);
	else if (p->pshb && p->n_a > 3)
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
