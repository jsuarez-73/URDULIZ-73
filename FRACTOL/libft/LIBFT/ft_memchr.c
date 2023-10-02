/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:04:40 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/15 20:04:40 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memchr(const void *s, int c, t_size n)
{
	t_size	cntr;

	cntr = 0;
	while (cntr < n)
	{
		if (*(unsigned char *)(s + cntr) == (unsigned char) c)
			return ((void *)(s + cntr));
		cntr++;
	}
	return (NULL);
}
