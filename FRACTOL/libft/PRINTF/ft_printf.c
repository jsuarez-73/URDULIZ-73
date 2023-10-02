/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:23:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/10 14:13:05 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fstr, ...)
{
	t_fstr	root;
	va_list	list;
	int		len;

	root.nxt = NULL;
	root.q_nd = 0;
	if (fstr == NULL)
		return (0);
	va_start(list, fstr);
	if (ft_tree_drv((char *)fstr, &root) == 0)
		return (ft_freemch(&root));
	ft_nd_drv(&root);
	if (ft_parser(&root) == 0)
		return (ft_freemch(&root));
	ft_exp_arg(list, &root);
	va_end(list);
	len = ft_outmch(&root);
	ft_freemch(&root);
	return (len);
}
