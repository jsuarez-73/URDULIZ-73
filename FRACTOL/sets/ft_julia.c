/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:55:09 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/01 13:03:30 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_julia(t_xsrv *sf, double xp, double yp)
{
	int		cntr;
	double	zx;
	double	zy;
	double	zx_a;

	cntr = 0;
	zx = xp;
	zy = yp;
	zx_a = 0;
	while (cntr++ <= sf->iter && (zx * zx + zy * zy) <= 4.0)
	{
		zx_a = zx;
		zx = zx * zx - zy * zy + sf->cx;
		zy = 2 * zx_a * zy + sf->cy;
	}
	cntr = cntr * sf->crange / (sf->iter + 1);
	if (cntr > sf->crange)
		return (sf->crange);
	else
		return (cntr);
}
