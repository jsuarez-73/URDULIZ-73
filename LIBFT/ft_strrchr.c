/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:57:27 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/15 17:57:27 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*l_found;
	t_size	counter;
	t_size	index;

	counter = 0;
	index = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			index = counter;
			l_found = s;
		}
		counter++;
		s++;
	}
	if (index != 0)
	{
		return (l_found + index);
	}
	return (c);
}
