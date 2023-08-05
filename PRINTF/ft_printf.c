/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:23:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/05 18:24:52 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fstr)
{
	t_fstr	root;

	root.nxt = NULL;
	root.q_nd = 0;
	/*ft_parser has been tested, at the moment not bugs found, however
	more tests must be reviewed*/
	ft_parser((char *)fstr, &root);
	// printf("D:\t%d\t%s\t%s\n", (root.q_nd), (root.nxt->nxt->nxt->nxt->nxt->nxt->nxt->lm.off),
	// 										(root.nxt->nxt->nxt->nxt->nxt->nxt->nxt->lm.end));
	printf("D:\t%s\t%s\t%d",root.lm.off, root.lm.end, root.q_nd);
	return (0);
}

int	main(void)
{
	printf("%2$-*3$.*1$d %1$d\n", 11, 8, 10);
	printf("%2$-10.*1$d %1$d\n", 4, 3); //show that it's not compulsory for field and precision an $ style.
	printf("%*.*d %*.*d%%\n", -15, 10, 20, 10, 10, 29); //Shows if possible use * but any of them request an argument, as also any <conv>
	// ft_printf("%%%Esta%+-2312hhs%asdadsasdasd%aaaaaaaaaaax%aaaaaaaaaaaaa");
	ft_printf("Eaaaaaaaaaaa aaaaa aaaaa aaaaaaaaaaaaaaaaak"); //Para este caso crea un nodo
	//vacio, cuando tiene porcentaje no crea tal nodo.
	return (0);
}