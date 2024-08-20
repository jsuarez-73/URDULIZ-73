/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:48:36 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/14 12:48:36 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	ft_strlcat(char *dest, const char *src, t_size n)
{
	t_size	size_dest;
	char	*tmp;

	size_dest = ft_strlen(dest);
	if (n <= size_dest)
		return (n + ft_strlen(src));
	tmp = dest;
	dest += size_dest;
	n--;
	while (*src != '\0' && n-- > size_dest)
		*dest++ = *src++;
	*dest = '\0';
	return (ft_strlen(src) + ft_strlen(tmp));
}
