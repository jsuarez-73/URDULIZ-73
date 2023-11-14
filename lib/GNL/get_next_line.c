/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:13:34 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/12 19:49:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	lst_gnl;
	t_gnl			*gl;

	lst_gnl.watcher = LOCK;
	lst_gnl.linea = NULL;
	lst_gnl.b_ln = 0;
	if (ft_search_add(&lst_gnl, fd, &gl) == NULL)
		return (NULL);
	while (lst_gnl.watcher)
	{
		if (gl->e_bf == (gl->buf + gl->b_rd))
		{
			lst_gnl.watcher = ft_guard(&lst_gnl.linea, &gl, &lst_gnl, fd);
			if (lst_gnl.watcher == RETURN)
				return (lst_gnl.linea);
		}
		else
			if (ft_mem_mng(&lst_gnl.linea, &gl, &lst_gnl.b_ln) == 1)
				return (lst_gnl.linea);
	}
	return (NULL);
}
