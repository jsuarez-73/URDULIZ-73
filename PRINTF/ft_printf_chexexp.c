/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chexexp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:55:40 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 11:42:05 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_wr_chex(t_wrtr *wr, char *off)
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
			ft_hash_vldtn(mp, off, wr, UPPER);

	}
	else
	{
		if (mp.hash != 0 && *(u_int *) wr->d != 0)
			ft_hex_vldtn(off, wr, 2, UPPER);
		else
			ft_hex_vldtn(off, wr, 0, UPPER);
	}
}

int ft_chex_exp(t_nd *nd, unsigned int hx)
{
	t_wrtr			wr;
	unsigned int	(*ft_mchex)(t_wrtr *);
	void			(*ft_chex)(t_wrtr *, char *);

	ft_mchex = ft_mng_hex;
	ft_chex = ft_wr_chex;
	wr.nd = nd;
	wr.dt = ft_mkhex(hx, UPPER);
	wr.d = &hx;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mchex) == 0)
		return (0);
	ft_wr_mch(&wr, ft_chex);
	free(wr.dt);
	return (1);
}