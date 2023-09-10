/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_treedrv_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:50:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/10 18:46:42 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

static int	ft_setter_helper(char *fstr, char **off, char *off_pc, t_fstr *rt)
{
	t_nd	nd;
	t_lm	lm;

	nd.is_lf = 1;
	lm.off = *off;
	lm.end = off_pc - 1;
	if (ft_add_nd(rt, nd, lm) == 0)
		return (0);
	if (*fstr != 0)
	{
		nd.is_lf = 0;
		lm.off = off_pc;
		lm.end = fstr;
		if (ft_add_nd(rt, nd, lm) == 0)
			return (0);
	}
	*off = fstr + 1;
	return (1);
}

static int	ft_setter(char *fstr, char **off, char *off_pc, t_fstr *root)
{
	t_nd	nd;
	t_lm	lm;

	if (*off == off_pc)
	{
		nd.is_lf = 0;
		lm.off = *off;
		lm.end = fstr;
		if (ft_add_nd(root, nd, lm) == 0)
			return (0);
		*off = fstr + 1;
		return (1);
	}
	if (ft_setter_helper(fstr, off, off_pc, root) == 0)
		return (0);
	return (1);
}

static int	ft_set_nd(char **fstr, t_fstr *root, char **off)
{
	char	*conv;
	char	*off_pc;

	conv = "cspdiuxX%";
	off_pc = *fstr;
	*fstr = ft_matcher(*fstr, conv);
	if (ft_setter(*fstr, off, off_pc, root) == 0)
		return (0);
	return (1);
}

int	ft_tree_drv(char *fstr, t_fstr *root)
{
	char	*off;

	off = fstr;
	while (*fstr != 0)
	{
		if (*fstr == '%')
			if (ft_set_nd(&fstr, root, &off) == 0)
				return (0);
		if (*fstr != 0)
			fstr++;
	}
	if (fstr != off)
		if (ft_set_nd(&fstr, root, &off) == 0)
			return (0);
	return (1);
}
