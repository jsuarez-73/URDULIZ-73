/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:41:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/30 21:22:23 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_uns	ft_id_big(int *st, t_uns f_id, t_uns n_id)
{
	t_uns	id_b;
	int		big;

	id_b = n_id;
	big = *(st + id_b);
	while (n_id > f_id)
	{
		if (big < *(st + n_id - 1))
		{
			big = *(st + n_id - 1);
			id_b = n_id - 1;
		}
		n_id--;
	}
	return (id_b);
}

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
