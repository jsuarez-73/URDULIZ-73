/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scheme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:52:43 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 19:23:04 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_get_color_scheme(t_xsrv *sf)
{
	int	color;
	int color_r;
	int color_g;
	int	cntr;

	sf->colors = (int *)malloc(sizeof(int) * sf->crange);
	if (!sf->colors)
		return ;
	color = 0x3e06c2;
	color_r = (color >> 16);
	color_g = (color >> 8);
	cntr = 0;
	while (cntr < sf->crange)
	{
		color_r = color_r + 16 * cntr;
		color_g = color_g + 16 * cntr;
		color = color + 16 * cntr;
		*(sf->colors + cntr) = (color_r << 16) | (color_g << 8) | (color);
		cntr++; 
	}
	*(sf->colors + cntr) = 0;
}
