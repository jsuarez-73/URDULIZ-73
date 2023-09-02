/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:05:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 20:50:38 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_mknum(char *end, char *off, t_map *map, t_ndtype type)
{
	static int	pow;

	if (pow == 0)
		pow = 1;
	if (*end >= '0' && *end <= '9')
	{
		if (type == FIELD)
			map->fnum += (*end - '0') * pow;
		else if (type == PRCSN)
			map->pnum += (*end - '0') * pow;
		pow *= 10;
	}
	if (type == FIELD)
	{
		if (end == off)
			pow = 1;
		
	}
	else if (type == PRCSN)
	{
		if (end == off + 1)
			pow = 1;
	}	
}

void	ft_get_maps(t_map *map, char *off, char *end, t_ndtype type)
{
	while (end >= off)
	{
		if (*end == '#' && type == FLAGS)
			(*map).hash++;
		if (*end == '+' && type == FLAGS)
			(*map).plus++;
		if (*end == '-' && type == FLAGS)
			(*map).minus++;
		if (*end == '0' && type == FLAGS)
			(*map).zero++;
		if (*end == ' ' && type == FLAGS)
			(*map).space++;
		if (*end == '*' && type == FIELD)
			(*map).fstar++;
		if (*end != '*' && type == FIELD)
			ft_mknum(end, off, map, FIELD);
		if (*end == '*' && type == PRCSN)
			(*map).pstar++;
		if (*end == '.' && type == PRCSN)
			(*map).ppoint++;
		if (*end != '.' && *end != '*' && type == PRCSN)
			ft_mknum(end, off, map, PRCSN);
		end--;
	}
}

void	ft_init_map(t_map *map)
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
	map->sgned = 0;
}

int	ft_vldtn_cons(t_map map, char *conv)
{
	if (map.plus > 0 && ((*conv != 'd' && *conv != 'i') || map.space > 0))
		return (0);
	if (map.space > 0 && ((*conv != 'd' && *conv != 'i') || map.plus > 0))
		return (0);
	if (map.ppoint > 0 && (map.zero > 0 || *conv == 'p' || *conv == 'c'))
		return (0);
	if (map.hash > 0 && *conv != 'x' && *conv != 'X')
		return (0);
	if (map.zero > 0)
		if (map.minus > 0 || *conv == 's' || *conv == 'c' || *conv == 'p')
			return (0);
	if (*conv == '%')
	{
		if (map.plus > 0 || map.hash > 0 || map.minus > 0 || map.zero > 0)
			return (0);
		if (map.space > 0 || map.fstar > 0 || map.fnum > 0 || map.pstar > 0)
			return (0);
		if (map.pnum > 0 || map.ppoint > 0)
			return (0);
	}
	if ((map.fstar != 0 && map.fnum != 0) || (map.pstar != 0 && map.pnum != 0))
		return (0);
	return (1);
}

int	ft_exp_arg(va_list list, t_fstr *root)
{
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		if (root->nd.is_lf == 0)
		{
			if (*(root->lm.end) == 's')
				ft_str_exp(&root->nd, va_arg(list, char *));
			else if (*(root->lm.end) == 'd')
				ft_dbl_exp(&root->nd, va_arg(list, int));
			else if (*(root->lm.end) == 'c')
				ft_chr_exp(&root->nd, va_arg(list, int));
			else if (*(root->lm.end) == 'i')
				ft_dbl_exp(&root->nd, va_arg(list, int));
			else if (*(root->lm.end) == 'x')
				ft_hex_exp(&root->nd, va_arg(list, unsigned int));
			else if (*(root->lm.end) == 'u')
				ft_usgn_exp(&root->nd, va_arg(list, unsigned int));
			else if (*(root->lm.end) == 'X')
				ft_chex_exp(&root->nd, va_arg(list, unsigned int));
			else if (*(root->lm.end) == 'p')
				ft_ptr_exp(&root->nd, va_arg(list, void *));
			else if (*(root->lm.end) == '%')
				ft_per_exp(&root->nd);
		}
		root = root->nxt;
	}
	return (1);
}