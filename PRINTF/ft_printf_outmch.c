/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outmch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 09:59:03 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 15:03:27 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_outmch(t_fstr *root)
{
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		if (root->nd.is_lf == 1)
			write(0, root->lm.off, root->lm.end - root->lm.off + 1);
		else if (root->nd.is_lf == 0)
			write(0, root->nd.lf.off, root->nd.lf.end - root->nd.lf.off + 1);
		root = root->nxt;
	}
	return (1);
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
	return (1);
}
