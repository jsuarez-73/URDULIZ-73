/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:53:07 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/15 19:53:07 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	if (n == 0)
		return (0);
	n--;
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		if (n--)
		{
			s1++;
			s2++;
		}
		else
			return (0);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
