/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:43:05 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 11:42:17 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_wr_str(t_wrtr *wr, char *off)
{
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *(wr->end_dt)--;
		else if (wr->nd->map.zero != 0)
			*off = '0';
		else
			*off = ' ';
	}
	else
	{
		if (off <= wr->off + wr->sz - 1)
			*off = *(wr->off_dt)++;
		else if (wr->nd->map.zero != 0)
			*off = '0';
		else
			*off = ' ';
	}
}

static u_int	ft_mng_str(t_wrtr *wr)
{
	t_map	mp;
	
	mp = wr->nd->map;
	if (mp.fnum > mp.pnum)
	{
		if (mp.ppoint != 0)
			return (mp.fnum);
		else
		{
			if (mp.fnum > wr->sz)
				return (mp.fnum);
			else
				return (wr->sz);
		}
	}
	else if (mp.pnum <= wr->sz && mp.ppoint != 0)
		return (mp.pnum);
	else
		return (wr->sz);
}

static char	*ft_mkstr(t_map mp, char *str, u_int *dlen)
{
	char	*dt;
	u_int	size;

	if (mp.pnum <= *dlen && mp.ppoint != 0)
		size = sizeof(char) * mp.pnum;
	else
		size = sizeof(char) * (*dlen);
	dt = (char *) malloc(size + 1);
	if(dt == NULL)
		return (NULL);
	*dlen = size;
	*(dt + size) = '\0';
	while (size--)
		*(dt + size) = *(str + size);
	return (dt);
}

int ft_str_exp(t_nd *nd, char *str)
{
	t_wrtr			wr;
	void			(*ft_str)(t_wrtr *, char *);
	unsigned int	(*ft_mstr)(t_wrtr *);
	
	ft_str = ft_wr_str;
	ft_mstr = ft_mng_str;
	wr.nd = nd;
	wr.sz = ft_strlen(str);
	wr.d = str;
	if (ft_mem_mng(&wr, ft_mstr) == 0)
		return (0);
	wr.dt = ft_mkstr(nd->map, str, &wr.sz);
	if (wr.dt == NULL)
		return (0);
	ft_wr_mch(&wr, ft_str);
	free(wr.dt);
	return (1);
}