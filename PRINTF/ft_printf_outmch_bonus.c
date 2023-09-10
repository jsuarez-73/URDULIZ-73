/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outmch_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 09:59:03 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/10 18:45:55 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_outwr_helper(t_fstr *root, int *len)
{
	int	exp;

	exp = 0;
	if (root->nd.is_lf == 1)
	{
		exp = root->lm.end - root->lm.off + 1;
		if (root->lm.off != NULL && exp > 0)
		{
			write(0, root->lm.off, root->lm.end - root->lm.off + 1);
			*len += root->lm.end - root->lm.off + 1;
		}
	}
	else if (root->nd.is_lf == 0)
	{
		exp = root->nd.lf.end - root->nd.lf.off + 1;
		if (root->nd.lf.off != NULL && exp > 0)
		{
			write(0, root->nd.lf.off, root->nd.lf.end - root->nd.lf.off + 1);
			*len += root->nd.lf.end - root->nd.lf.off + 1;
		}
	}
}

int	ft_outmch(t_fstr *root)
{
	unsigned int	q_nd;
	int				len;

	q_nd = root->q_nd;
	len = 0;
	while (q_nd--)
	{
		ft_outwr_helper(root, &len);
		root = root->nxt;
	}
	return (len);
}

int	ft_freemch(t_fstr *root)
{
	unsigned int	q_nd;
	t_fstr			*tmp;
	unsigned int	counter;

	q_nd = root->q_nd;
	tmp = root;
	counter = 0;
	while (q_nd--)
	{
		if (root->nd.is_lf == 0)
			free(root->nd.lf.off);
		tmp = root->nxt;
		if (counter++ != 0)
			free(root);
		root = tmp;
	}
	return (0);
}
