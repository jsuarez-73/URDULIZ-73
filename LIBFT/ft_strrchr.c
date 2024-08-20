/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:57:27 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/15 17:57:27 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	t_size	len;

	len = ft_strlen(s);
	while (len && *(s + len) != (unsigned char) c)
		len--;
	if (*(s + len) == (unsigned char) c)
		return ((char *)(s + len));
	return (NULL);
}
