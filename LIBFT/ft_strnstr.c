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
	t_size	h;
	t_size	j;

	h = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	else if (ft_strlen(s1) < ft_strlen(s2))
		return (NULL);
	while (*(s1 + h) != '\0')
	{
		j = 0;
		while (*(s1 + h + j) == *(s2 + j) && (h + j) < n)
		{
			if (*(s1 + h + j) == '\0' && *(s1 + j) == '\0')
				return ((char *)(s1 + h));
			j++;
		}
		if (*(s2 + j) == '\0' || *(s1 + h + j) == '\0')
			return ((char *)(s1 + h));
		h++;
	}
	return (NULL);
}
