/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:05:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/06 20:25:42 by jsuarez-         ###   ########.fr       */
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

/*the constraints validations has been modified due to the way
that the tests known so far take the format string without having
in consideration the CFLAGS when we compile the program, giving us
a program which could output answer ignoring warnings.*/
int	ft_vldtn_cons(t_map m, char *c)
{
	if (*c == '%')
		return (1);
	if (m.plus > 0 && ((*c != 'd' && *c != 'i') || m.space > 0))
		return (0);
	if (m.space > 0 && ((*c != 'd' && *c != 'i' && *c != 's') || m.plus > 0))
		return (0);
	if (m.ppoint > 0 && (m.zero > 0 || *c == 'p' || *c == 'c'))
		return (0);
	if (m.hash > 0 && *c != 'x' && *c != 'X')
		return (0);
	if (m.zero > 0)
		if (m.minus > 0 || *c == 's' || *c == 'c' || *c == 'p')
			return (0);
	if ((m.fstar != 0 && m.fnum != 0) || (m.pstar != 0 && m.pnum != 0))
		return (0);
	return (1);
}
