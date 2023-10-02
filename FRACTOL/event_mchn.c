/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mchn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:48:50 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/02 08:12:45 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_btn_down(int btn, int x, int y, t_xsrv *sf)
{
	if (btn == SCROLL_UP)
	{
		sf->mx *= 0.90;
		sf->my *= 0.90;
		sf->tx += 0.11 * ((double)x / (double)sf->w - 0.5) * sf->mx;
		sf->ty -= 0.11 * ((double)y / (double)sf->h - 0.5) * sf->my;
	}
	else if (btn == SCROLL_DW)
	{
		sf->tx -= 0.11 * ((double)x / (double)sf->w - 0.5) * sf->mx;
		sf->ty += 0.11 * ((double)y / (double)sf->h - 0.5) * sf->my;
		sf->mx /= 0.90;
		sf->my /= 0.90;
	}
	else
		return (0);
	ft_render(sf);
	return (1);
}

static int	ft_key_down(int key, t_xsrv *sf)
{
	if (key == ESC)
	{
		if (sf->colors)
			free(sf->colors);
		mlx_loop_end(sf->mlx);
	}
	else if (key == ARR_UP)
		sf->ty += 0.1 * sf->my;
	else if (key == ARR_DW)
		sf->ty -= 0.1 * sf->my;
	else if (key == ARR_LF)
		sf->tx -= 0.1 * sf->mx;
	else if (key == ARR_RG)
		sf->tx += 0.1 * sf->mx;
	else
		return (0);
	ft_render(sf);
	return (1);
}

static int	ft_cross_down(t_xsrv *sf)
{
	if (sf->colors)
		free(sf->colors);
	mlx_destroy_image(sf->mlx, sf->img);
	mlx_destroy_window(sf->mlx, sf->win);
	mlx_loop_end(sf->mlx);
	return (1);
}

void	ft_hook_init(t_xsrv *sf)
{
	mlx_mouse_hook(sf->win, ft_btn_down, sf);
	mlx_key_hook(sf->win, ft_key_down, sf);
	mlx_hook(sf->win, DESTROY, DEF_MSK, ft_cross_down, sf);
}
