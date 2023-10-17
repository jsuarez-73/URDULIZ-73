/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:26:56 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/19 17:01:00 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_inside(char c, char const *set)
{
	while (*set != '\0')
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*new;
	const char	*start;
	const char	*end;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	end = s1 + ft_strlen(s1);
	while (ft_inside(*start, set) && *start != '\0')
		start++;
	while (ft_inside(*(end - 1), set) && end > start)
		end--;
	new = (char *)malloc(end - start + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, start, end - start + 1);
	return (new);
}
