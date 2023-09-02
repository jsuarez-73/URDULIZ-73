/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptrexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:56:22 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 21:13:43 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static u_int	ft_mng_ptr(t_wrtr *wr)
{
	t_map	mp;
	int		hashed;

	mp = wr->nd->map;
	if (*(long *) wr->d == 0)
		hashed = 0;
	else
		hashed = 2;
	if (mp.fnum >= wr->sz + hashed)
		return (mp.fnum);
	else
		return (wr->sz + hashed);
}

static void	ft_wr_ptr(t_wrtr *wr, char *off)
{
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *wr->end_dt--;
		else if (off == wr->off - wr->sz && *(long *) wr->d != 0)
			*off = 'x';
		else if (off == wr->off - wr->sz - 1 && *(long *) wr->d != 0)
			*off = '0';
		else
			*off = 'k';
	}
	else
	{
		if (off == wr->off && *(long *) wr->d != 0)
			*off = '0';
		else if (off == wr->off + 1 && *(long *) wr->d != 0)
			*off = 'x';
		else if (off < wr->off + wr->sz + 2 && *(long *) wr->d != 0)
			*off = *wr->off_dt++;
		else if (off < wr->off + wr->sz && *(long *) wr->d == 0)
			*off = *wr->off_dt++;
		else
			*off = 'k';
	}
}

int ft_ptr_exp(t_nd *nd, void *ptr)
{
	long			ptr_d;
	t_wrtr			wr;
	unsigned int	(*ft_mptr)(t_wrtr *);
	void			(*ft_ptr)(t_wrtr *, char *);

	ptr_d = (long) ptr;
	ft_mptr = ft_mng_ptr;
	ft_ptr = ft_wr_ptr;
	wr.nd = nd;
	if (ptr_d != 0)
		wr.dt = ft_mkhex(ptr_d, LOWER);
	else
		wr.dt = "(nil)";
	wr.d = &ptr_d;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mptr) == 0)
		return (0);
	ft_wr_mch(&wr, ft_ptr);
	printf("D:\t Debuggin ptr: %s\t%p\t%ld\t%s\n", nd->lf.off, ptr, ptr_d, wr.dt);
	return (1);
}