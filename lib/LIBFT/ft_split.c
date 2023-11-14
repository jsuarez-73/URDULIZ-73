/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:42:12 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/19 17:12:06 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_mknd(char ***ptr, t_size q_nd)
{
	char	**tmp;

	if (q_nd == 1)
	{
		tmp = (char **) malloc(sizeof(char *) * (q_nd + 1));
		if (tmp == NULL)
			return (0);
		*(tmp + q_nd) = NULL;
		*ptr = tmp;
		return (1);
	}
	else
	{
		tmp = (char **) malloc(sizeof(char *) * (q_nd + 1));
		if (tmp == NULL)
			return (0);
		*(tmp + q_nd) = NULL;
		while (**ptr != NULL)
			*tmp++ = *(*ptr)++;
		free(*ptr - q_nd + 1);
		*ptr = (tmp - q_nd + 1);
		return (1);
	}
}

static short	ft_loop(char ***ptr, char *clean, char *off, char ch)
{
	t_size	q_nd;
	char	*end;

	q_nd = 0;
	end = clean + ft_strlen(clean);
	while (clean <= end)
	{
		if (*clean != ch && *(clean - 1) == ch)
			off = clean;
		if ((*clean == ch || *clean == '\0') && *(clean - 1) != ch)
		{
			q_nd++;
			if (ft_mknd(ptr, q_nd) == 0)
			{
				if (*ptr != NULL)
					free(*ptr);
				return (0);
			}
			*(*ptr + q_nd - 1) = ft_substr(off, 0, clean - off);
			if (*ptr + q_nd - 1 == NULL)
				return (0);
		}
		clean++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;
	char		*clean;
	char		*off;
	char		ch;

	ch = c;
	ptr = NULL;
	clean = ft_strtrim(s, &ch);
	if (!clean)
		return (NULL);
	else if (*clean == '\0')
	{
		free(clean);
		ptr = (char **)malloc(sizeof(char **) * 1);
		if (ptr == NULL)
			return (NULL);
		*ptr = NULL;
		return (ptr);
	}
	off = clean;
	ft_loop(&ptr, clean, off, c);
	free(clean);
	return (ptr);
}
