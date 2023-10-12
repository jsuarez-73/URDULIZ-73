/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:59:38 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/12 20:59:38 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, t_size n)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
		*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	return (dest);
}
