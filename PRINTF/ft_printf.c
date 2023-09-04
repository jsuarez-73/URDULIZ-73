/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:23:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/04 18:16:12 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*Se deben realizar las respectivas verificaciones para las funciones *_exp*/
int	ft_printf(const char *fstr, ...)
{
	t_fstr	root;
	va_list	list;

	root.nxt = NULL;
	root.q_nd = 0;
	if (fstr == NULL)
		return (0);
	va_start(list, fstr);
	if (ft_tree_drv((char *)fstr, &root) == 0)
		return (0);
	ft_nd_drv(&root);
	if (ft_parser(&root) == 0)
		return (0);
	if (ft_exp_arg(list, &root) == 0)
		return (0);
	va_end(list);
	ft_outmch(&root);
	ft_freemch(&root);
	return (1);
}
