/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:13:34 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/06/30 14:07:37 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	lst_gnl;
	t_gnl			*gl;
	char			*linea;
	t_watch			watcher;
	unsigned int	b_ln;

	watcher = LOCK;
	linea = NULL;
	b_ln = 0;
	if (ft_search_add(&lst_gnl, fd, &gl) == NULL)
		return (NULL);
	while (watcher)
	{
		if (gl->e_bf == (gl->buf + gl->b_rd))
		{
			watcher = ft_guard(&linea, &gl, &lst_gnl, fd);
			if (watcher == RETURN)
				return (linea);
		}
		else
			if (ft_mem_mng(&linea, &gl, &b_ln) == 1)
				return (linea);
	}
	return (NULL);
}
