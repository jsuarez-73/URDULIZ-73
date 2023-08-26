/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treedrv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:50:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/17 18:53:24 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*Summary: this function is encharge to reserve
memory and make the tree structure expandable.*/
static int	ft_add_nd(t_fstr *root, t_nd nd, t_lm lm)
{
	t_fstr	*tmp;

	if (root->q_nd != 0)
	{
		tmp = (t_fstr *)malloc(sizeof(t_fstr));
		if (tmp == NULL)
			return (0);
		tmp->nd = nd;
		tmp->lm = lm;
		tmp->nxt = NULL;
		(root->q_nd)++;
		while (root->nxt != NULL)
			root = root->nxt;
		root->nxt = tmp;
		return (1);
	}
	root->nd = nd;
	root->lm = lm;
	root->nxt = NULL;
	(root->q_nd)++;
	return (1);
}

/*Summary: This function receive the percent position as
str and the set of conversor specifiers as set, it's meant
to return the position where one conversor specifiers match
with the str which is the same fstr*/
static char	*ft_matcher(char *str, char *set)
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

/*Summary: This function receive the arguments fstr which has
the position where the match was found, off which has the 
position where the String start after de last match or the
beginning, off_pc which has the position of the percent found
and the root which is the tree structure, it's encharge to 
set all the nodes in the structure.*/
static int	ft_setter(char *fstr, char **off, char *off_pc, t_fstr *root)
{
	t_nd	nd;
	t_lm	lm;

	if (*off == off_pc)
	{
		nd.is_lf = 0;
		lm.off = *off;
		lm.end = fstr;
		ft_add_nd(root, nd, lm);
		*off = fstr + 1;
		return (0);
	}
	nd.is_lf = 1;
	lm.off = *off;
	lm.end = off_pc - 1;
	ft_add_nd(root, nd, lm);
	if (*fstr != 0)
	{
		nd.is_lf = 0;
		lm.off = off_pc;
		lm.end = fstr;
		ft_add_nd(root, nd, lm);
	}
	*off = fstr + 1;
	return (0);
}

/*Summary: this function initializate the set of 
conversor specifiers that this program has as meta
character as well as start the matcher and the setter.*/
static int	ft_set_nd(char **fstr, t_fstr *root, char **off)
{
	char	*conv;
	char	*off_pc;

	conv = "cspdiuxX%";
	off_pc = *fstr;
	*fstr = ft_matcher(*fstr, conv);
	ft_setter(*fstr, off, off_pc, root);
	return (0);
}

/*Summary: The function move a pointer up to reach 0
in case it find a meta % it must pass the pointer to
that meta %, as well as root which is the structure 
tree and the off pointer whihc point always to the
start of the string or the start the rest of the string
when the nodes has been settled*/
int	ft_tree_drv(char *fstr, t_fstr *root)
{
	char	*off;

	off = fstr;
	while (*fstr != 0)
	{
		if (*fstr == '%')
			ft_set_nd(&fstr, root, &off);
		fstr++;
	}
	if (fstr != off)
		ft_set_nd(&fstr, root, &off);
	return (0);
}
