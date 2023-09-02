/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:53:39 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 21:13:32 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

u_int	ft_mng_hex(t_wrtr *wr)
{
	int		hashed;
	t_map	mp;

	hashed = 0;
	mp = wr->nd->map;
	if (mp.hash != 0 && *(u_int *) wr->d != 0)
		hashed = 2;
	if (*(u_int *) wr->d == 0 && mp.fnum >= 1 && mp.fnum >= mp.pnum)
		return (mp.fnum);
	else if (*(u_int *) wr->d == 0 && mp.pnum >= 1 && mp.pnum >= mp.fnum)
		return (mp.pnum);
	else if (*(u_int *) wr->d == 0 && mp.ppoint != 0)
		return (0);
	else if (mp.fnum > mp.pnum + hashed)
	{
		if (mp.fnum <= wr->sz + hashed)
			return (wr->sz + hashed);
		else
			return (mp.fnum);
	}
	else if (mp.pnum > wr->sz)
		return (mp.pnum + hashed);
	else
		return (wr->sz + hashed);
}

void ft_hex_vldtn(char *off, t_wrtr *wr, int f, t_caphex capital)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (mp.hash != 0 && off == wr->off && *(int *) wr->d != 0)
		*off = '0';
	else if (mp.hash != 0 && off == wr->off + 1 && *(int *) wr->d != 0)
		*off = 23 + capital;
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum - wr->sz + f)
		*off = '0';
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum + f && !exp)
		*off = *wr->off_dt++;
	else if (mp.pnum <= wr->sz && off < wr->off + wr->sz + f && !exp)
		*off = *wr->off_dt++;
	else
		*off = 'k';
}

void	ft_hash_vldtn(t_map mp, char *off, t_wrtr *wr, t_caphex cp)
{
	int	exp;

	exp = (mp.hash != 0 && *(u_int *) wr->d != 0);
	if (mp.zero != 0 && exp && off > wr->end + 1)
		*off = '0';
	else if (mp.zero != 0 && exp && off == wr->end + 1)
		*off = 23 + cp;
	else if (mp.zero != 0 && exp && off == wr->end)
		*off = '0';
	else if (mp.zero != 0 && (mp.hash == 0 || *(u_int *) wr->d == 0))
		*off = '0';
	else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
		*off = '0';
	else if (mp.pnum > wr->sz && exp && off == wr->off - mp.pnum)
		*off = 23 + cp;
	else if (mp.pnum > wr->sz && exp && off == wr->off - mp.pnum - 1)
		*off = '0';
	else if (mp.pnum <= wr->sz && exp && off == wr->off - wr->sz)
		*off = 23 + cp;
	else if (mp.pnum <= wr->sz && exp && off == wr->off - wr->sz - 1)
		*off = '0';
	else
		*off = 'k';
}

static void	ft_wr_hex(t_wrtr *wr, char *off)
{
	t_map	mp;
	int		exp;
	
	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && !exp)
			*off = *wr->end_dt--;
		else
			ft_hash_vldtn(mp, off, wr, LOWER);

	}
	else
	{
		if (mp.hash != 0 && *(u_int *) wr->d != 0)
			ft_hex_vldtn(off, wr, 2, LOWER);
		else
			ft_hex_vldtn(off, wr, 0, LOWER);
	}
}

int ft_hex_exp(t_nd *nd, unsigned int hex)
{
	t_wrtr			wr;
	unsigned int	(*ft_mhex)(t_wrtr *);
	void			(*ft_hex)(t_wrtr *, char *);

	ft_mhex = ft_mng_hex;
	ft_hex = ft_wr_hex;
	wr.nd = nd;
	wr.dt = ft_mkhex(hex, LOWER);
	wr.d = &hex;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mhex) == 0)
		return (0);
	ft_wr_mch(&wr, ft_hex);
	printf("D:\t Debuggin hex: %s\t%d\t%s\n", nd->lf.off, hex, wr.dt);
	return (1);
}