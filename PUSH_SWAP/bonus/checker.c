/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:09:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 08:32:45 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	main(int argc, char **argv)
{
	t_push	p;
	char	*line;
	t_list	lst;
	short	flg;

	ft_check_args(argc, argv, &p);
	lst.content = NULL;
	lst.next = NULL;
	flg = 1;
	while (flg)
	{
		line = get_next_line(STD_IN);
		if (line)
		{
			if (ft_check_in(line, ft_strlen(line), &p, &lst))
				ft_push_lst(&lst, line, ft_strlen(line), &p);
			free(line);
		}
		else
			flg = 0;
	}
	ft_exec_lst(&lst, &p);
}
