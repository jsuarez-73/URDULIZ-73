/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:12:47 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/19 19:46:45 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_add_dig(char d, char *numstr, short sgn)
{
	char	*tmp;
	t_size	len;

	if (numstr == NULL)
	{
		numstr = (char *)malloc(2 + sgn);
		if (numstr == NULL)
			return (NULL);
		*(numstr + sgn + 1) = '\0';
		*(numstr + sgn) = d;
		return (numstr);
	}
	else
	{
		len = ft_strlen(numstr + sgn);
		tmp = (char *)malloc(len + 2 + sgn);
		if (tmp == NULL)
			return (NULL);
		*(tmp + len + sgn + 1) = '\0';
		while (len--)
			*(tmp + len + sgn + 1) = *(numstr + len + sgn);
		free(numstr);
		*(tmp + sgn) = d;
		return (tmp);
	}
}

char	*ft_itoa(int n)
{
	long	num;
	char	*numstr;

	num = (long) n;
	numstr = NULL;
	if (n < 0)
		num *= -1;
	if (n == 0)
	{
		numstr = ft_add_dig('0', numstr, n < 0);
		if (numstr == NULL)
			return (NULL);
	}
	while (num != 0)
	{
		numstr = ft_add_dig((num % 10) + '0', numstr, n < 0);
		if (numstr == NULL)
			return (NULL);
		num = (num - (num % 10)) / 10;
	}
	if ((n < 0) == 1)
		*numstr = '-';
	return (numstr);
}
