/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:23:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 20:31:40 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*Se deben realizar las respectivas verificaciones para las funciones del tree_drv
en que caso de que ocurra algun error de asignacion de memoria, asi como tambien
se debe controlar el fstr.*/
/*Se deben realizar test para la verificacion del format string.*/
/*Se debe liberar la memoria asignada al arbol de derivacion root.*/

/************IMPORTANTE****************/
/*El ft_print_parser tiene comentado la validacion que
devuelve cuando el format string es incorrecto! No olvidar
descomentarlo.*/
int	ft_printf(const char *fstr, ...)
{
	t_fstr	root;
	va_list	list;
	t_fstr	*tst;
	int		counter;
	int		end;

	tst = &root;
	root.nxt = NULL;
	root.q_nd = 0;
	counter = 0;
	if (fstr == NULL)
		return (0);
	va_start(list, fstr);
	ft_tree_drv((char *)fstr, &root);
	ft_nd_drv(&root);
	ft_parser(&root);
	ft_exp_arg(list, &root);
	va_end(list);
	end = (int) tst->q_nd;
	while (counter++ < end)
	{
		if (tst->nd.is_lf == 0)
		{
			// if (tst->nd.lf != NULL)
			// 	printf("D:\t Lo tenemos aqui : %s\t %s\n", tst->nd.lf, tst->lm.off);
			printf("D:\tmap: %p\t plus:%i\thash:%i\tminus:%d\tzero:%d\tspace:%d\tfnum:%d\tfstar:%d\tpnum:%d\tpstar:%d\tppoint:%d\tsgned:%d\n",
			&tst->nd.map, tst->nd.map.plus, tst->nd.map.hash, tst->nd.map.minus, tst->nd.map.zero, tst->nd.map.space, tst->nd.map.fnum,
			tst->nd.map.fstar, tst->nd.map.pnum, tst->nd.map.pstar, tst->nd.map.ppoint, tst->nd.map.sgned);
		}	
		// printf("D:\t node: %p\t off: %s\tend:%s\tis_lf:%d\n", tst, tst->lm.off, tst->lm.end, tst->nd.is_lf);
		tst = tst->nxt;
	}
	return (0);
}

int	main(void)
{
	int	test;

	test = 15;
	printf("%2$+*3$.*1$d %1$d\n", 2, 1, test);
	printf("%2$-+10.*3$d %1$d\n", 10, 3, 5); //show that it's not compulsory for field and precision an $ style.
	printf("E%%%iaaaa%20.skkk%-10ubbb%#xWWW%20pZZZ\n", 0, "Holaaaa", 0, -123, &test);
	ft_printf("EEE%%%04.saaa%-15c%-+10.3d%20paaa%#xbbb%010u", "Holaaaa", 'B', 0, &test, -123, 0);
	return (0);
}