/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:15:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/12 19:52:58 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_mng(t_gnl *lst, t_gnl *gl, int buf_sz)
{
	t_gnl	*tmp;

	if (gl->fd == lst->fd)
	{
		if (gl->next == NULL)
		{
			lst->fd = 0;
			lst->e_bf = NULL;
			lst->s_buf = NULL;
			return ;
		}
		lst->fd = (gl->next)->fd;
		lst->e_bf = lst->buf + ((gl->next)->e_bf - (gl->next)->buf);
		lst->b_rd = (gl->next)->b_rd;
		lst->s_buf = lst->buf + ((gl->next)->s_buf - (gl->next)->buf);
		while (buf_sz--)
			*(lst->buf + buf_sz) = *((gl->next)->buf + buf_sz);
		tmp = (gl->next);
		lst->next = (gl->next)->next;
		return (free(tmp));
	}
	while ((lst->next)->fd != gl->fd)
		lst = lst->next;
	lst->next = gl->next;
	free(gl);
}

int	ft_guard(char **ln, t_gnl **gl, t_gnl *ls, int fd)
{
	(*gl)->b_rd = read(fd, (*gl)->buf, BUFFER_SIZE);
	if ((*gl)->b_rd > 0)
	{
		(*gl)->s_buf = (*gl)->buf;
		(*gl)->e_bf = (*gl)->buf;
	}
	else if ((*gl)->b_rd == 0)
	{
		ft_free_mng(ls, *gl, BUFFER_SIZE);
		if (*ln != NULL)
			return (2);
		return (0);
	}
	else
	{
		ft_free_mng(ls, *gl, BUFFER_SIZE);
		return (0);
	}
	return (1);
}

static int	ft_cp_mng(char **ln, t_gnl **gl, unsigned int *b_ln)
{
	char			*tmp;
	unsigned int	counter;

	counter = 0;
	tmp = (char *)malloc(((*gl)->e_bf - (*gl)->s_buf) + *b_ln + 1);
	*(tmp + ((*gl)->e_bf - (*gl)->s_buf) + *b_ln) = '\0';
	if (tmp == NULL)
		return (0);
	while (counter < *b_ln)
	{
		*(tmp + counter) = *(*ln + counter);
		counter++;
	}
	*b_ln += ((*gl)->e_bf - (*gl)->s_buf);
	while ((*gl)->s_buf < (*gl)->e_bf)
		*(tmp + counter++) = *(*gl)->s_buf++;
	if (*ln != NULL)
		free(*ln);
	*ln = tmp;
	counter = 0;
	return (1);
}

int	ft_mem_mng(char **ln, t_gnl **gl, unsigned int *b_ln)
{
	while ((*gl)->e_bf < (*gl)->buf + (*gl)->b_rd && *((*gl)->e_bf)++ != '\n')
		;
	if (*((*gl)->e_bf - 1) == '\n')
	{
		if (ft_cp_mng(ln, gl, b_ln) == 0)
			return (0);
		return (1);
	}	
	else
		if (ft_cp_mng(ln, gl, b_ln) == 0)
			return (0);
	return (0);
}

t_gnl	*ft_search_add(t_gnl *gnl, int fd, t_gnl **gl)
{
	if (gnl->e_bf != NULL)
	{
		while (gnl->fd != fd && gnl->next != NULL)
			gnl = gnl->next;
		if (gnl->fd == fd)
			return (*gl = gnl);
		*gl = (t_gnl *)malloc(sizeof(t_gnl));
		if (*gl == NULL)
			return (NULL);
		(*gl)->fd = fd;
		(*gl)->e_bf = (*gl)->buf;
		(*gl)->s_buf = (*gl)->buf;
		(*gl)->next = NULL;
		(*gl)->b_rd = 0;
		gnl->next = *gl;
		return (*gl);
	}
	gnl->e_bf = gnl->buf;
	gnl->s_buf = gnl->buf;
	gnl->fd = fd;
	gnl->next = NULL;
	gnl->b_rd = 0;
	return (*gl = gnl);
}
