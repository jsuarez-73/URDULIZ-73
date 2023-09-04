/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nddrv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:39:18 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 15:00:00 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Summary: This function receive the percent position as
str and the set of conversor specifiers as set, it's meant
to return the position where one conversor specifiers match
with the str which is the same fstr*/
char	*ft_matcher(char *str, char *set)
{
	char	*conv;
	short	flg;

	conv = set;
	flg = 0;
	while (*str++ != 0 && flg == 0)
	{
		while (*conv != 0 && flg == 0)
			if (*str == *conv++)
				flg = 1;
		conv = set;
	}
	return (str - 1);
}

static void	ft_trip_helper(char **off, t_lm *lm, short *fnd, char **set)
{
	while (**set != 0 && *fnd != 2)
	{
		if (**set == **off && *fnd == 0)
		{
			*fnd = 1;
			(*lm).off = *off;
			break ;
		}
		else if (**set == **off && *fnd == 1)
			break ;
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

static void	ft_chopper(t_nd *p_rt, char *off, char *end)
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
}

/*Initialization a chopping to the nodes.
We do the initialization here, because it's gonna
be very useful when we will get the leaves to 
put the conversor expanded.*/
void	ft_nd_drv(t_fstr *root)
{
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		root->nd.lf.off = NULL;
		root->nd.lf.end = NULL;
		if (root->nd.is_lf == 0)
			ft_chopper(&root->nd, root->lm.off, root->lm.end);
		root = root->nxt;
	}
}
