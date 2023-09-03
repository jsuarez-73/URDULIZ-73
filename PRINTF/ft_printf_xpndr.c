/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xpndr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 09:53:44 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 09:55:56 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_exp_vldtn(t_fstr *root, va_list list)
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

int	ft_exp_arg(va_list list, t_fstr *root)
{
	unsigned int	q_nd;

	q_nd = root->q_nd;
	while (q_nd--)
	{
		if (root->nd.is_lf == 0)
			ft_exp_vldtn(root, list);
		root = root->nxt;
	}
	return (1);
}