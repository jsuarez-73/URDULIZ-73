/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:03:22 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/02 08:12:03 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_help_msg(void)
{
	ft_printf("%23s\n", "HELP");
	ft_printf("%s\n\t%s", "NAME", "fractol - Generate your own Julia,");
	ft_printf("Mandelbrot or cubic set\n\n");
	ft_printf("%s\n\t%s\n", "SINOPSIS", "fractol <fractal> [-cr=int],");
	ft_printf("\t%s\n\n", "fractol Julia [-cr=int] [-cx=double] [-cy=double]");
	ft_printf("%s\n\t%s", "DESCRIPTION", "Generate the three possibles");
	ft_printf(" fractal (Julia, Mandelbrot or Cubic)\n\n");
	ft_printf("%s\n\t%s", "OPTIONS", "-cx, (axis-coord)\n\t\tAllow change");
	ft_printf(" the initial x-coordinate in Julia\n");
	ft_printf("\t%s", "-cy, (ord-coord)\n\t\tAllow change the initial");
	ft_printf(" y-coordinate in Julia\n");
	ft_printf("\t%s", "-cr, (color-range)\n\t\tAllow to change the color");
	ft_printf(" range to render the fractal\n\n");
	ft_printf("%s\n", "double number must have this format: [-][d*].[d*s*]");
	ft_printf("%s\n\n", "where d represent a digit and s any char string");
	ft_printf("%s\n\t\t%s\n", "AUTHOR", "Written by Jesus Suarez");
	ft_printf("%30s\n", "01/10/2023");
	exit(0);
	return (1);
}
