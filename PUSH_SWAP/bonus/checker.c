/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:09:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/02 23:31:54 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
/*Corregir la funcion check_in para unificar ft_clean_lst con ft_clean_psh*/
int	main(int argc, char **argv)
{
	t_push	p;
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	t_list	lst;
	short	flg;

	ft_check_args(argc, argv, &p);
	*(buf + BUFFER_SIZE) = '\0';
	lst.content = NULL;
	lst.next = NULL;
	flg = 1;
	while (flg)
	{
		line = get_next_line(STD_IN);
		if (line)
		{
			if (ft_check_in(line, ft_strlen(line), &p, &lst))
				ft_push_lst(&lst, line, ft_strlen(line));
			free(line);
		}
		else
			flg = 0;
	}
	ft_exec_lst(&lst, &p);
}
