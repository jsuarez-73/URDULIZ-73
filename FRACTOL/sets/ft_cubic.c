/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:33:01 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 17:00:11 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_cubic(t_xsrv *sf, double xp, double yp)
{
	t_uns	cntr;
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
		zx = zx * zx * zx - 3.0 * zx * zy * zy + sf->cx;
		zy = 3.0 * zx_a * zx_a * zy - zy * zy * zy + sf->cy;
	}
	return (cntr * sf->crange / sf->iter);
}
