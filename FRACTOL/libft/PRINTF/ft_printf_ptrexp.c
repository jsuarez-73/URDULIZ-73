/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptrexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:56:22 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/21 20:10:10 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_uns	ft_mng_ptr(t_wrtr *wr)
{
	t_map	mp;
	int		hashed;

	mp = wr->nd->map;
	if (mp.ppoint == 0 && mp.pnum == 0 && *(long *)wr->d == 0)
		wr->sz = 1;
	hashed = 2;
	if (mp.fnum > mp.pnum + hashed)
	{
		if (mp.fnum > wr->sz + hashed)
			return (mp.fnum);
		else
			return (wr->sz + hashed);
	}
	else if (mp.pnum > wr->sz)
		return (mp.pnum + hashed);
	else
		return (wr->sz + hashed);
}

static void	ft_ptr_vldrg(t_wrtr *wr, char *off, char *off_h, char dflt)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (*(long *)wr->d == 0 && mp.ppoint == 0 && mp.pnum == 0);
	if (off == off_h - 1 && exp)
		*off = 'x';
	else if (off == off_h - 2 && exp)
		*off = '0';
	else if (off == off_h && !exp)
		*off = 'x';
	else if (off == off_h - 1 && !exp)
		*off = '0';
	else if (off == off_h && exp)
		*off = '0';
	else
		*off = dflt;
}

static void	ft_ptr_vldlf(t_map mp, char *off, t_wrtr *wr, char *off_s)
{
	int	exp;

	exp = (*(long *) wr->d == 0);
	if (off == off_s)
		*off = '0';
	else if (off == off_s + 1)
		*off = 'x';
	else if (mp.ppoint == 0 && mp.pnum == 0 && exp && off == off_s + 2)
		*off = '0';
	else if (mp.pnum > wr->sz && off <= off_s + mp.pnum - wr->sz + 1)
		*off = '0';
	else if (mp.pnum > wr->sz && off <= off_s + mp.pnum + 1 && !exp)
		*off = *wr->off_dt++;
	else if (mp.pnum < wr->sz && off <= off_s + wr->sz + 1)
		*off = *wr->off_dt++;
	else if (mp.pnum < wr->sz && exp && off <= wr->off + wr->sz - 1)
		*off = *wr->off_dt++;
	else
		*off = ' ';
}

static void	ft_wr_ptr(t_wrtr *wr, char *off)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (*(long *)wr->d == 0);
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && !exp)
			*off = *wr->end_dt--;
		else if (mp.zero != 0 && mp.ppoint == 0)
			ft_ptr_vldrg(wr, off, wr->end + 2, '0');
		else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
			*off = '0';
		else if (mp.pnum > wr->sz)
			ft_ptr_vldrg(wr, off, wr->off - mp.pnum, ' ');
		else if (!exp)
			ft_ptr_vldrg(wr, off, wr->off - wr->sz, ' ');
		else
			ft_ptr_vldrg(wr, off, wr->off, ' ');
	}
	else
		ft_ptr_vldlf(mp, off, wr, wr->off);
}

int	ft_ptr_exp(t_nd *nd, void *ptr)
{
	long			ptr_d;
	t_wrtr			wr;
	unsigned int	(*ft_mptr)(t_wrtr *);
	void			(*ft_ptr)(t_wrtr *, char *);

	ptr_d = (long) ptr;
	ft_mptr = ft_mng_ptr;
	ft_ptr = ft_wr_ptr;
	ft_init_wr(&wr);
	wr.nd = nd;
	if (ptr_d != 0)
		wr.dt = ft_mkhex(ptr_d, LOWER);
	else
		wr.dt = "";
	wr.d = &ptr_d;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen_p(wr.dt);
	if (ft_mem_mng_p(&wr, ft_mptr) != 0)
		ft_wr_mch(&wr, ft_ptr);
	if (ptr_d != 0)
		free(wr.dt);
	return (1);
}
