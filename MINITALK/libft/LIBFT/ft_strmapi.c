/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:48:14 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/19 20:49:11 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int id, char c))
{
	char	*chr;
	t_size	len;
	t_size	cntr;

	len = ft_strlen(s);
	chr = (char *)malloc(len + 1);
	cntr = 0;
	if (chr == NULL)
		return (NULL);
	while (cntr < len)
	{
		*(chr + cntr) = f(cntr, *s++);
		cntr++;
	}
	*(chr + cntr) = '\0';
	return (chr);
}
