/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:51:37 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/13 11:51:37 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	t_size	cntr;

	cntr = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
		while (n--)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	else
	{
		while (n--)
		{
			*(unsigned char *)(dest + cntr) = *(unsigned char *)(src + cntr);
			cntr++;
		}
	}
	return (dest);
}
