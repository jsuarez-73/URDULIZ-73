/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dblexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:45:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 15:13:51 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_uns	ft_mng_dbl(t_wrtr *wr)
{
	t_map	mp;
	int		sgned;
	int		exp;

	sgned = 0;
	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (mp.plus != 0 || mp.sgned != 0 || mp.space != 0)
		sgned = 1;
	if (exp && mp.fnum >= 1)
		return (mp.fnum);
	else if (exp && mp.fnum < 1)
		return (sgned);
	else if (mp.fnum > mp.pnum)
	{
		if (mp.fnum <= wr->sz)
			return (wr->sz + sgned);
		else
			return (mp.fnum);
	}
	else if (mp.pnum >= wr->sz)
		return (mp.pnum + sgned);
	else
		return (wr->sz + sgned);
}

static void	ft_dbl_vldtns(t_map mp, char *off, t_wrtr *wr, int f)
{
	int	exp;

	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (off == wr->off && mp.sgned != 0)
		*off = '-';
	else if (off == wr->off && mp.plus != 0)
		*off = '+';
	else if (off == wr->off && mp.space != 0)
		*off = ' ';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - wr->sz - f)
		*off = '0';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - f)
		*off = *wr->off_dt++;
	else if (mp.pnum < wr->sz && off <= wr->off + wr->sz - f && !exp)
		*off = *wr->off_dt++;
	else
		*off = ' ';
}

static void	ft_dbl_sgnvld(t_wrtr *wr, char *off, char *end, char dflt)
{
	int		exp;
	t_map	mp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (mp.sgned != 0 && off == end && !exp)
		*off = '-';
	else if (mp.plus != 0 && off == end && !exp)
		*off = '+';
	else if (mp.space != 0 && off == end && !exp)
		*off = ' ';
	else if (exp && mp.plus != 0 && off == wr->off)
		*off = '+';
	else
		*off = dflt;
}

static void	ft_wr_dbl(t_wrtr *wr, char *off)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && !exp)
			*off = *wr->end_dt--;
		else if (mp.zero != 0)
			ft_dbl_sgnvld(wr, off, wr->end, '0');
		else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
			*off = '0';
		else if (mp.pnum > wr->sz)
			ft_dbl_sgnvld(wr, off, wr->off - mp.pnum, ' ');
		else
			ft_dbl_sgnvld(wr, off, wr->off - wr->sz, ' ');
	}
	else
	{
		if (mp.sgned != 0 || mp.plus != 0 || mp.space != 0)
			ft_dbl_vldtns(mp, off, wr, 0);
		else
			ft_dbl_vldtns(mp, off, wr, 1);
	}
}

int	ft_dbl_exp(t_nd *nd, int dbl)
{
	t_wrtr			wr;
	unsigned int	(*ft_mdbl)(t_wrtr *);
	void			(*ft_dbl)(t_wrtr *, char *);

	ft_mdbl = ft_mng_dbl;
	ft_dbl = ft_wr_dbl;
	if (dbl < 0)
	{
		nd->map.sgned = 1;
		dbl *= -1;
	}
	wr.nd = nd;
	wr.d = &dbl;
	wr.dt = ft_mkdbl(dbl);
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mdbl) == 0)
		return (0);
	ft_wr_mch(&wr, ft_dbl);
	free(wr.dt);
	return (1);
}
