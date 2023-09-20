/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:06:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/16 18:02:38 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(t_size nmemb, t_size size)
{
	char	*ptr;
	t_size	ttl;

	ttl = nmemb * size;
	if (ttl > 2147483647)
		return (NULL);
	ptr = (char *) malloc(ttl);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, ttl);
	return (ptr);
}
