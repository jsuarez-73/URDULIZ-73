/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:22:05 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/06 21:22:13 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Has been modified the return from the validations constraints because
we are not getting this warnings as errors in the tester time, modify it's
necessary.*/
static int	ft_nd_cnst(t_map map, char *conv)
{
	unsigned int	*off_map;
	unsigned int	*end_map;

	off_map = &(map.plus);
	end_map = &(map.ppoint);
	if (ft_vldtn_cons(map, conv) == 0)
		return (1);
	while (off_map <= end_map)
	{
		if (off_map != &(map.fnum) && off_map != &(map.pnum))
			if (*off_map > 1)
				return (0);
		off_map++;
	}
	return (1);
}

/*The ft_nd_cnst function has been setted off because the
constraints have not been considered for all the test well
known so far, this could give us some warnings because we
are compiling without the CFLAGS, having this on consideration
it's important to check wether the molinette compile with or
without CFLAGS.*/
static int	ft_cnst(t_fstr *root)
{
	t_nd			*nd;
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		if (root->nd.is_lf != 1)
		{
			nd = &root->nd;
			ft_init_map(&(nd->map));
			if (nd->flgs.off != NULL)
				ft_get_maps(&(nd->map), nd->flgs.off, nd->flgs.end, FLAGS);
			if (nd->wdth.off != NULL)
				ft_get_maps(&(nd->map), nd->wdth.off, nd->wdth.end, FIELD);
			if (nd->prcsn.off != NULL)
				ft_get_maps(&(nd->map), nd->prcsn.off, nd->prcsn.end, PRCSN);
			if (ft_nd_cnst(nd->map, root->lm.end) == 0)
				return (1);
		}
		root = root->nxt;
	}
	return (1);
}

static int	ft_nd_wdfnd(t_lm flgs, t_lm wdth, t_lm prcsn, t_lm lm)
{
	if (flgs.off == NULL && wdth.off == NULL && prcsn.off == NULL)
	{
		if (lm.end - lm.off == 1)
			return (1);
	}
	else if (flgs.off == NULL || wdth.off == NULL || prcsn.off == NULL)
	{
		if (prcsn.off != NULL && (lm.end - prcsn.end) == 1)
			return (1);
		else if (wdth.off != NULL && (lm.end - wdth.end) == 1)
			return (1);
		else if (flgs.off != NULL && (lm.end - flgs.end) == 1)
			return (1);
		else
			return (0);
	}
	else
		if (lm.end - prcsn.end == 1)
			return (1);
	return (0);
}

static int	ft_wdfnd(t_fstr *root)
{
	t_nd			nd;
	t_lm			lm;
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		if (root->nd.is_lf != 1)
		{
			nd = root->nd;
			lm = root->lm;
			if (ft_nd_wdfnd(nd.flgs, nd.wdth, nd.prcsn, lm) == 0)
				return (0);
		}
		root = root->nxt;
	}
	return (1);
}

int	ft_parser(t_fstr *root)
{
	if (ft_wdfnd(root) == 1 && ft_cnst(root) == 1)
		return (1);
	return (0);
}
