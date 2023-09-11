/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_perexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:56:59 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/11 10:42:52 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_uns	ft_mng_per(t_wrtr *wr)
{
	t_map	mp;

	mp = wr->nd->map;
	if (mp.fnum > 0)
		return (mp.fnum);
	else
		return (1);
}

static void	ft_wr_per(t_wrtr *wr, char *off)
{
	t_map	mp;

	mp = wr->nd->map;
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *wr->end_dt--;
		else if (mp.zero != 0 && mp.ppoint == 0)
			*off = '0';
		else
			*off = ' ';
	}
	else
	{
		if (off <= wr->off + wr->sz - 1)
			*off = *wr->off_dt++;
		else
			*off = ' ';
	}
}

int	ft_per_exp(t_nd *nd)
{
	t_wrtr			wr;
	unsigned int	(*ft_mper)(t_wrtr *);
	void			(*ft_per)(t_wrtr *, char *);

	ft_mper = ft_mng_per;
	ft_per = ft_wr_per;
	wr.nd = nd;
	wr.dt = (char *) malloc(sizeof(char) * 1);
	if (wr.dt == NULL)
		return (0);
	*wr.dt = '%';
	wr.sz = 1;
	wr.d = NULL;
	if (ft_mem_mng(&wr, ft_mper) != 0)
		ft_wr_mch(&wr, ft_per);
	free(wr.dt);
	return (1);
}
