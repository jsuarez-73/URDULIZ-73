/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:56:29 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/11 18:54:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef enum e_ndtype
{
	FLAGS,
	FIELD,
	PRCSN
}	t_ndtype;

typedef struct s_map
{
	unsigned short	plus;
	unsigned short	hash;
	unsigned short	minus;
	unsigned short	zero;
	unsigned short	space;
	unsigned short	fnum;
	unsigned short	fstar;
	unsigned short	pnum;
	unsigned short	pstar;
	unsigned short	ppoint;
}	t_map;

typedef struct t_elem
{
	char	*off;
	char	*end;
}	t_lm;

typedef struct s_nd
{
	char	*lf;
	t_lm	prcsn;
	t_lm	flgs;
	t_lm	wdth;
	t_map	map;
	short	is_lf;
}	t_nd;

typedef struct s_fstr
{
	t_nd			nd;
	t_lm			lm;
	unsigned int	q_nd;
	struct s_fstr	*nxt;
}	t_fstr;

int	ft_printf(const char *fstr);
int	ft_tree_drv(char *fstr, t_fstr *root);
int	ft_nd_drv(t_fstr *root);
int	ft_parser(t_fstr *root);

#endif
