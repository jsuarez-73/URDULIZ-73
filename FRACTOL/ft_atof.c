/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:48:02 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 20:52:39 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static double	ft_atof(char *str)
{
	short	pnt;
	double	num;
	int		pow;

	if (str == NULL || *str == '\0' || !ft_isdigit(*str))
		return (0);
	num = 0;
	pnt = 0;
	pow = 10;
	while (*str != '\0' && pnt <= 1)
	{
		if (ft_isdigit(*str) && pnt < 1)
			num = 10 * num + (*str - '0');
		else if (ft_isdigit(*str) && pnt == 1)
		{
			num += (double)(*str - '0') / (double)pow;
			pow *= 10;
		}
		else if (*str == '.')
			pnt++;
		str++;
	}
	return (num);
}
//Primera prueba superada
int	main(void)
{
	printf("D:\t2345.3443: %f\n", ft_atof("a2345.3443"));
	return (0);
}