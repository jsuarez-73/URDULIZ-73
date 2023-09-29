/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:37:49 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 20:53:08 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//Revisar esta funcion para incorporar en check_others
static double	ft_atof(char *str)
{
	short	pnt;
	double	num;
	int		pow;

	if (str == NULL || *str == '\0' || !ft_isdigit(*str))
		return (0);
	num = 0;
	pnt = 0;
	pow = 10;
	while (*str != '\0' && pnt <= 1)
	{
		if (ft_isdigit(*str) && pnt < 1)
			num = 10 * num + (*str - '0');
		else if (ft_isdigit(*str) && pnt == 1)
		{
			num += (*str - '0') / pow;
			pow *= 10;
		}
		else if (*str == '.')
			pnt++;
		str++;
	}
	return (num);
}

static void	ft_check_others(int argc, char **argv, t_xsrv *sf)
{
	int	cntr;

	cntr = 0;
	printf("D:\t argv:%s\t argv + 1:%s\n", *argv, *(argv + 1));
	while (argc--)
	{
		if (ft_strncmp(*(argv + cntr), "-cr", 3) == 0)
		{
			sf->crange = ft_atoi(*(argv + cntr + 1));
			cntr += 2;
			argc--;
			if (sf->crange != 0)
				sf->arg_msk |= 1;
		}
		else if (sf->chosen == 'J')
		{
			if (ft_strncmp(*(argv + cntr), "-cx", 3) == 0)
			{
				sf->cx = ft_atoi(*(argv + cntr + 1));
				cntr += 2;
				argc--;
				if (sf->cx != 0)
					sf->arg_msk |= (1 << 1);
			}
			else if (ft_strncmp(*(argv + cntr), "-cy", 3) == 0)
			{
				sf->cy = ft_atoi(*(argv + cntr + 1));
				cntr += 2;
				argc--;
				if (sf->cy != 0)
					sf->arg_msk |= (1 << 2);
			}
		}
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
			exit(1); //Falta implementar correctamente la salida
		if (argc > 2)
			ft_check_others(argc - 2, argv + 2, sf);
	}
	else
		exit(1);
}

void	ft_init(t_xsrv *sf)
{
	sf->win = mlx_new_window(sf->mlx, DEF_WIDTH, DEF_HEIGHT, "FRACTOL");
	sf->img = mlx_new_image(sf->mlx, DEF_WIDTH, DEF_HEIGHT);
	sf->off = mlx_get_data_addr(sf->img, &sf->bpp, &sf->ln_len, &sf->endian);
	sf->iter = 42;
	sf->w = DEF_WIDTH;
	sf->h = DEF_HEIGHT;
	sf->my = 4.0;
	sf->mx = 4.0;
	sf->tx = 0;
	sf->ty = 0;
	ft_set_attr(sf);
	// sf->cx = 0.285;
	// sf->cy = -0.01;
}
