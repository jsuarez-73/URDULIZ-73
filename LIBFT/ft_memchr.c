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
	t_size	counter;
	void	*ptr_null;

	counter = 0;
	while (counter < n)
	{
		if (*(unsigned char *) s == (unsigned char) c)
		{
			return (s);
		}
	}
	return (ptr_null);
}
