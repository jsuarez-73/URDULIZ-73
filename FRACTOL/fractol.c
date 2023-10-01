/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:52:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/01 17:55:50 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_xsrv	sf;

	sf.arg_msk = 0;
	ft_attr_mngr(&sf, argc, argv);
	sf.mlx = mlx_init();
	if (!sf.mlx)
		return (-1);
	if (!ft_init(&sf))
		return (-1);
	if (!ft_get_color_scheme(&sf))
		return (-1);
	ft_render(&sf);
	ft_hook_init(&sf);
	mlx_loop(sf.mlx);
	return (0);
}
