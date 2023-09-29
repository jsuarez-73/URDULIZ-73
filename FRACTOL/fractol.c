/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:52:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 19:23:04 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*No olvidar que colors hace malloc para almacenar rango de colores,
se debe liberar memoria.*/
int	main(int argc, char **argv)
{
	t_xsrv	sf;

	sf.arg_msk = 0;
	ft_attr_mngr(&sf, argc, argv);
	sf.mlx = mlx_init();
	ft_init(&sf);
	ft_get_color_scheme(&sf);
	ft_render(&sf);
	ft_hook_init(&sf);
	mlx_loop(sf.mlx);
	return (0);
}
