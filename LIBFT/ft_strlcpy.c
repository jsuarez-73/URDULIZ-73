/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:24:54 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/13 21:24:54 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	ft_strlcpy(char *dest, const char *src, t_size n)
{
	t_size	src_len;

	src_len = ft_strlen(src);
	if (n-- != 0)
	{
		while (*src != '\0' && n--)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (src_len);
}
