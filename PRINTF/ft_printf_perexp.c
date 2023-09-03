/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_perexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:56:59 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/03 11:41:58 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_per_exp(t_nd *nd)
{
	nd->lf.off = (char *) malloc(sizeof(char) * 1);
	if (nd->lf.off == NULL)
		return (0);
	*nd->lf.off = '%';
	nd->lf.end = nd->lf.off;
	return (1);
}