/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wrmch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 09:47:49 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 15:04:47 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lf_rg(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	char	*off;
	char	*end;

	off = wr->nd->lf.off;
	end = wr->nd->lf.end;
	wr->off_dt = wr->dt;
	wr->end_dt = wr->dt + wr->sz - 1;
	wr->end = end;
	wr->off = off;
	wr->rg_lf = 0;
	while (off <= end)
		f(wr, off++);
}

void	ft_rg_lf(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	char	*off;
	char	*end;

	off = wr->nd->lf.off;
	end = wr->nd->lf.end;
	wr->off_dt = wr->dt;
	wr->end_dt = wr->dt + wr->sz - 1;
	wr->end = off;
	wr->off = end;
	wr->rg_lf = 1;
	while (end >= off)
	{
		f(wr, end--);
	}
}

void	ft_wr_mch(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	if (wr->nd->map.minus != 0)
		ft_lf_rg(wr, f);
	else
		ft_rg_lf(wr, f);
}
