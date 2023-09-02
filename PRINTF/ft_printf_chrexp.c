/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chrexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:48:17 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 21:13:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static u_int	ft_mng_chr(t_wrtr *wr)
{
	t_map	mp;

	mp = wr->nd->map;
	if (mp.fnum > wr->sz)
		return (mp.fnum);
	else
		return (wr->sz);
}

static void	ft_wr_chr(t_wrtr *wr, char *off)
{
	if (off == wr->off)
		*off = *wr->dt;
	else
		*off = 'k';
}

static char	*ft_mkchr(char chr)
{
	char	*dt;

	dt = (char *) malloc(sizeof(char) * 2);
	if (dt == NULL)
		return (NULL);
	*(dt + sizeof(char) * 1) = '\0';
	*dt = chr;
	return (dt);

}
/*Testeado levemente, pero funcional hasta el momento.*/
int ft_chr_exp(t_nd *nd, unsigned char chr)
{
	unsigned int	(*ft_mchr)(t_wrtr *);
	void	(*ft_chr)(t_wrtr *, char *);
	t_wrtr	wr;

	ft_chr = ft_wr_chr;
	ft_mchr = ft_mng_chr;
	wr.sz = 1;
	wr.nd = nd;
	wr.dt = ft_mkchr(chr);
	wr.d = &chr;
	if (wr.dt == NULL)
		return (0);
	if (ft_mem_mng(&wr, ft_mchr) == 0)
		return (0);
	ft_wr_mch(&wr, ft_chr);
	printf("D:\t Debuggin chr: %s\t%d\n", nd->lf.off, chr);
	return (0);
}