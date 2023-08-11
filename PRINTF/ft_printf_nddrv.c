/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nddrv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:39:18 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/10 16:38:46 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*Algunas pruebas realizadas, falta realizar mas pruebas de nivel asi como disminuir
el tamano de la funcion ft_trip_set.*/
static void	ft_trip_helper(char **off, t_lm *lm, short *fnd, char **set)
{
	while (**set != 0 && *fnd != 2)
	{
		if (**set == **off && *fnd == 0)
		{
			*fnd = 1;
			(*lm).off = *off;
			break;
		}
		else if (**set == **off && *fnd == 1)
			break;
		else if (*(*set + 1) == 0 && **set != **off)
		{
			if (*fnd == 0)
				(*lm).off = NULL;
			*fnd = 2;
			(*lm).end = *off - 1;
		}
		(*set)++;
	}
}

static t_lm	ft_trip_set(char *off, char *end, char *set)
{
	t_lm	lm;
	char	*off_set;
	short	fnd;

	off_set = set;
	fnd = 0;
	while (off++ < end && fnd != 2)
	{
		ft_trip_helper(&off, &lm, &fnd, &set);
		set = off_set;
	}
	return (lm);
}

static int	ft_chopper(t_nd *p_rt, char *off, char *end)
{
	t_lm	lm;

	lm = ft_trip_set(off, end, "0-#+ ");
	p_rt->flgs.off = lm.off;
	p_rt->flgs.end = lm.end;
	lm = ft_trip_set(p_rt->flgs.end, end, "0123456789*");
	p_rt->wdth.off = lm.off;
	p_rt->wdth.end = lm.end;
	lm = ft_trip_set(p_rt->wdth.end, end, "0123456789.*");
	p_rt->prcsn.off = lm.off;
	p_rt->prcsn.end = lm.end;
	// printf("D:\t off flgs: %s\t end flgs: %s\n", p_rt->flgs.off, p_rt->flgs.end);
	// printf("D:\t off width: %s\t end_width: %s\n", p_rt->wdth.off, p_rt->wdth.end);
	// printf("D:\t off prcsn: %s\t end_prcsn: %s\n\n", p_rt->prcsn.off, p_rt->prcsn.end);

	return (0);
}

int	ft_nd_drv(t_fstr *root)
{
	t_fstr	*p_rt;

	p_rt = root;
	while (p_rt->nxt != NULL)
	{
		if (p_rt->nd.is_lf == 0)
			ft_chopper(&p_rt->nd, p_rt->lm.off, p_rt->lm.end);
		p_rt = p_rt->nxt;
	}
	return (0);
}