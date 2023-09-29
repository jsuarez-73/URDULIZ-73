/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mchn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:52:00 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 19:23:04 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"fractol.h"

static void	my_mlx_pixel_put(t_xsrv *sf, int x, int y, int color)
{
	char	*dst;

	dst = sf->off + (y * sf->ln_len + x * (sf->bpp / 8));
	*(unsigned int*)dst = color;
}

static int	ft_fractal_chosen(t_xsrv *sf, double xp, double yp)
{
	if (sf->chosen == 'M')
		return (ft_mondelbrot(sf, xp, yp));
	else if (sf->chosen == 'J')
		return (ft_julia(sf, xp, yp));
	else if (sf->chosen == 'C')
		return (ft_cubic(sf, xp, yp));
	else
		return (0);
}

void	ft_render(t_xsrv *sf)
{
	int		y;
	int		x;
	double	xp;
	double	yp;
	int		cntr;

	y = 0;
	while (y < sf->h)
	{
		x = 0;
		while (x < sf->w)
		{
			yp = sf->my * (0.5 - ((double)y / (double)sf->h)) + sf->ty;
			xp = sf->mx * (((double)x / (double)sf->w) - 0.5) + sf->tx;
			cntr = ft_fractal_chosen(sf, xp, yp);
			my_mlx_pixel_put(sf, x, y, *(sf->colors + cntr));
			x++;
		}
		y++;
	}
	mlx_clear_window(sf->mlx, sf->win);
	mlx_put_image_to_window(sf->mlx, sf->win, sf->img, 0, 0);
}
