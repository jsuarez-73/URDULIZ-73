/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mondelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:54:53 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 17:00:05 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_mondelbrot(t_xsrv *sf, double xp, double yp)
{
	t_uns	cntr;
	double	zx;
	double	zy;
	double	zx_a;

	cntr = 0;
	zx = 0;
	zy = 0;
	zx_a = 0;
	while (cntr++ <= sf->iter && (zx * zx + zy * zy) <= 4.0)
	{
		zx_a = zx;
		zx = zx * zx - zy * zy + xp;
		zy = 2 * zx_a * zy + yp;
	}
	return (cntr * sf->crange / sf->iter);
}
