/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:23:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/11 20:23:35 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*Se deben realizar las respectivas verificaciones para las funciones del tree_drv
en que caso de que ocurra algun error de asignacion de memoria, asi como tambien
se debe controlar el fstr.*/
/*Se debe liberar la memoria asignada al arbol de derivacion root.*/
int	ft_printf(const char *fstr)
{
	t_fstr	root;

	root.nxt = NULL;
	root.q_nd = 0;
	if (fstr == NULL)
		return (0);
	ft_tree_drv((char *)fstr, &root);
	ft_nd_drv(&root);
	ft_parser(&root);
	return (0);
}

int	main(void)
{
	int	test;

	test = -15;
	printf("%2$+*3$.*1$d %1$d\n", 2, 1, test);
	printf("%2$-+10.*3$d %1$d\n", 4, 3, -5); //show that it's not compulsory for field and precision an $ style.
	printf("%% %*.*d%%\n", 20, 10, 10); //Shows if possible use * but any of them request an argument, as also any <conv>
	// ft_printf("%%%Esta%+-2312hhs%asdadsasdasd%aaaaaaaaaaax%aaaaaaaaaaaaa");
	ft_printf("E%.1000****%%   #+-+-+-+-+-+-000001002030.*****xaaaa%saaaaaa% #-+010**2*3*.1231sk");
	return (0);
}