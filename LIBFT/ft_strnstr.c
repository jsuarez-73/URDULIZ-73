/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:30:46 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/15 20:30:46 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, t_size n)
{
	t_size	c;

	c = 1;
	while (*s1 != '\0')
	{
		if (*s1 == *s2)
		{
			while (c <= n)
			{
				if (*(s2 + c) != *(s1 + c) && c != n && *(s2 + c) != '\0')
				{
					c++;
					break ;
				}
				else
				{
					if (c == n)
						return (*s1);
				}
				c ++;
			}
		}
		s1 += c;
		c = 1;
	}
}
