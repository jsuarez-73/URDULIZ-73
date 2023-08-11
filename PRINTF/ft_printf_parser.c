/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:22:05 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/11 20:31:56 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_maps(t_map *map, char *off, char *end, t_ndtype type)
{
	while (off <= end)
	{
		if (*off == '#' && type == FLAGS)
			(*map).hash++;
		if (*off == '+' && type == FLAGS)
			(*map).plus++;
		if (*off == '-' && type == FLAGS)
			(*map).minus++;
		if (*off == '0' && type == FLAGS)
			(*map).zero++;
		if (*off == ' ' && type == FLAGS)
			(*map).space++;
		if (*off == '*' && type == FIELD)
			(*map).fstar++;
		if (*off != '*' && type == FIELD)
			(*map).fnum++;
		if (*off == '*' && type == PRCSN)
			(*map).pstar++;
		if (*off == '.' && type == PRCSN)
			(*map).ppoint++;
		if (*off != '.' && *off != '*' && type == PRCSN)
			(*map).pnum++;
		off++;
	}
}

static void	ft_init_map(t_map *map)
{
	map->plus = 0;
	map->hash = 0;
	map->minus = 0;
	map->zero = 0;
	map->space = 0;
	map->fstar = 0;
	map->fnum = 0;
	map->pstar = 0;
	map->pnum = 0;
	map->ppoint = 0;
}

static int	ft_vldtn_cons(t_map map, char *lm_end)
{
	/*Implementar las restricciones ya organizadas en la agenda.
	Muy importante tener en cuenta la restriccion del %*/
	return (1);
}

static int	ft_nd_cnst(t_map map, char *lm_end)
{
	unsigned short	*off_map;
	unsigned short	*end_map;

	off_map = &(map.plus);
	end_map = &(map.ppoint);

	if (ft_vldtn_cons(map, lm_end) == 0)
		return 0;
	while (off_map <= end_map)
	{
		if (off_map != &(map.fnum) && off_map != &(map.pnum))
		{
			if (*off_set > 1)
				return (0);
		}
		off_map++;
	}
	return (1);
}

static int	ft_cnst(t_fstr *root)
{
	t_nd	nd;

	while (root->nxt != NULL)
	{
		if (root->nd.is_lf != 1)
		{
			nd = root->nd;
			ft_init_map(&(nd.map));
			if (nd.flgs.off != NULL)
				ft_get_maps(&(nd.map), nd.flgs.off, nd.flgs.end, FLAGS);
			if (nd.wdth.off != NULL)
				ft_get_maps(&(nd.map), nd.wdth.off, nd.wdth.end, FIELD);
			if (nd.prcsn.off != NULL)
				ft_get_maps(&(nd.map), nd.prcsn.off, nd.prcsn.end, PRCSN);
			if (ft_nd_cnst(nd.map, root->lm.end) == 0)
				return (0);
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
	t_nd	nd;
	t_lm	lm;

	while (root->nxt != NULL)
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