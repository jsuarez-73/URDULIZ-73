/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_perexp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:56:59 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 21:13:37 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_per_exp(t_nd *nd)
{
	nd->lf.off = (char *) malloc(sizeof(char) * 1);
	if (nd->lf.off == NULL)
		return (0);
	*nd->lf.off = '%';
	printf("D:\t Debuggin per: %s\n", nd->lf.off);
	return (1);
}