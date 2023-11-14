/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_usgnexp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:54:41 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/21 20:10:10 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_uns	ft_mng_usgn(t_wrtr *wr)
{
	t_map	mp;

	mp = wr->nd->map;
	if (*(t_uns *) wr->d == 0 && mp.fnum >= 1 && mp.fnum >= mp.pnum)
		return (mp.fnum);
	else if (*(t_uns *) wr->d == 0 && mp.pnum >= 1 && mp.pnum >= mp.fnum)
		return (mp.pnum);
	else if (*(t_uns *) wr->d == 0 && mp.ppoint != 0)
		return (0);
	else if (*(t_uns *) wr->d == 0 && mp.ppoint == 0)
		return (1);
	else if (mp.fnum > mp.pnum)
	{
		if (mp.fnum <= wr->sz)
			return (wr->sz);
		else
			return (mp.fnum);
	}
	else if (mp.pnum > wr->sz)
		return (mp.pnum);
	else
		return (wr->sz);
}

static char	*ft_mkusgn(unsigned int usgn)
{
	t_uns	num;
	char	*dt;
	t_uns	counter;
	char	*tmp;

	counter = 0;
	if (usgn == 0)
	{
		if (ft_mem_asgn(&tmp, &dt, '0', &counter) == NULL)
			return (NULL);
		else
			return (dt);
	}
	while (usgn > 0)
	{
		num = usgn % 10 + '0';
		usgn /= 10;
		if (ft_mem_asgn(&tmp, &dt, num, &counter) == NULL)
			return (NULL);
	}
	return (dt);
}

static void	ft_usgn_vldtn(t_wrtr *wr, char *off)
{
	t_map	mp;

	mp = wr->nd->map;
	if (mp.zero != 0 && off >= wr->end && mp.ppoint == 0)
		*off = '0';
	else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
		*off = '0';
	else
		*off = ' ';
}

static void	ft_wr_usgn(t_wrtr *wr, char *off)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(t_uns *) wr->d == 0);
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && !exp)
			*off = *wr->end_dt--;
		else
			ft_usgn_vldtn(wr, off);
	}
	else
	{
		if (mp.pnum > wr->sz && off < wr->off + mp.pnum - wr->sz)
			*off = '0';
		else if (mp.pnum > wr->sz && off < wr->off + mp.pnum && !exp)
			*off = *wr->off_dt++;
		else if (mp.pnum <= wr->sz && off < wr->off + wr->sz && !exp)
			*off = *wr->off_dt++;
		else
			*off = ' ';
	}
}

int	ft_usgn_exp(t_nd *nd, unsigned int usgn)
{
	t_wrtr			wr;
	unsigned int	(*ft_musgn)(t_wrtr *);
	void			(*ft_usgn)(t_wrtr *, char *);

	ft_musgn = ft_mng_usgn;
	ft_usgn = ft_wr_usgn;
	ft_init_wr(&wr);
	wr.nd = nd;
	wr.dt = ft_mkusgn(usgn);
	wr.d = &usgn;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen_p(wr.dt);
	if (ft_mem_mng_p(&wr, ft_musgn) != 0)
		ft_wr_mch(&wr, ft_usgn);
	free(wr.dt);
	return (1);
}
