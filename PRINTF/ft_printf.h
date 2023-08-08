/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:56:29 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/08 21:16:23 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# ifndef CONVSIZE
#  define CONVSIZE 9
# endif

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

#endif
