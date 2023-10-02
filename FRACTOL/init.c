/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:37:49 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/02 08:13:13 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_check_julia_attr(int *cntr, int *argc, char **argv, t_xsrv *sf)
{
	if (ft_strncmp(*(argv + *cntr), "-cx", 3) == 0)
	{
		sf->cx = ft_atof(*(argv + *cntr + 1));
		*cntr += 2;
		(*argc)--;
		if (sf->cx != 0)
			sf->arg_msk |= (1 << 1);
	}
	else if (ft_strncmp(*(argv + *cntr), "-cy", 3) == 0)
	{
		sf->cy = ft_atof(*(argv + *cntr + 1));
		*cntr += 2;
		(*argc)--;
		if (sf->cy != 0)
			sf->arg_msk |= (1 << 2);
	}
	else
		ft_help_msg();
}

static void	ft_check_others(int argc, char **argv, t_xsrv *sf)
{
	int	cntr;

	cntr = 0;
	while (argc-- > 0)
	{
		if (ft_strncmp(*(argv + cntr), "-cr", 3) == 0 && *(argv + cntr + 1))
		{
			sf->crange = ft_atoi(*(argv + cntr + 1));
			cntr += 2;
			argc--;
			if (sf->crange > 0 && sf->crange <= 100)
				sf->arg_msk |= 1;
		}
		else if (sf->chosen == 'J')
		{
			ft_check_julia_attr(&cntr, &argc, argv, sf);
		}
		else
			ft_help_msg();
	}
}

static void	ft_set_attr(t_xsrv *sf)
{
	if (sf->chosen == 'J')
	{
		if ((sf->arg_msk >> 1) == 0)
			sf->cx = -0.766667;
		if ((sf->arg_msk >> 2) == 0)
			sf->cy = -0.090000;
	}
	else
	{
		sf->cx = 0.4;
		sf->cy = 0.0;
	}
	if ((sf->arg_msk & 1) == 0)
		sf->crange = 10;
}

void	ft_attr_mngr(t_xsrv *sf, int argc, char **argv)
{
	if (argc >= 2)
	{
		if (ft_strncmp(*(argv + 1), "Mandelbrot", 10) == 0)
			sf->chosen = 'M';
		else if (ft_strncmp(*(argv + 1), "Julia", 5) == 0)
			sf->chosen = 'J';
		else if (ft_strncmp(*(argv + 1), "Cubic", 5) == 0)
			sf->chosen = 'C';
		else
			ft_help_msg();
		if (argc > 2)
			ft_check_others(argc - 2, argv + 2, sf);
	}
	else
		ft_help_msg();
}

int	ft_init(t_xsrv *sf)
{
	sf->win = mlx_new_window(sf->mlx, DEF_WIDTH, DEF_HEIGHT, "FRACTOL");
	if (!sf->win)
		return (0);
	sf->img = mlx_new_image(sf->mlx, DEF_WIDTH, DEF_HEIGHT);
	if (!sf->img)
		return (0);
	sf->off = mlx_get_data_addr(sf->img, &sf->bpp, &sf->ln_len, &sf->endian);
	sf->iter = 60;
	sf->w = DEF_WIDTH;
	sf->h = DEF_HEIGHT;
	sf->my = 4.0;
	sf->mx = 4.0;
	sf->tx = 0;
	sf->ty = 0;
	sf->colors = NULL;
	ft_set_attr(sf);
	return (1);
}
