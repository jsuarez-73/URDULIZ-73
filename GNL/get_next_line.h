/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:17:24 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/06/29 22:02:41 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFERSIZE
#  define BUFFERSIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	int				fd;
	char			*e_bf;
	char			*s_buf;
	char			buf[BUFFERSIZE];
	int				b_rd;
	struct s_gnl	*next;
}	t_gnl;

typedef enum e_watch
{
	LOCK = 1,
	UNLOCK = 0,
	RETURN = 2
}	t_watch;

char	*get_next_line(int fd);
t_gnl	*ft_search_add(t_gnl *gnl, int fd, t_gnl **gl);
int		ft_guard(char **ln, t_gnl **gl, t_gnl *ls, int fd);
int		ft_mem_mng(char **ln, t_gnl **gl, unsigned int *b_ln);

#endif
