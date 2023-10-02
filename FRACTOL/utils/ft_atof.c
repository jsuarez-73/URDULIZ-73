/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:01:44 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/02 08:06:57 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *s)
{
	short	pnt;
	double	num;
	t_size	pow;
	short	sgn;

	if (s == NULL || *s == '\0' || !(*s == '-' || ft_isdigit(*s) || *s == '.'))
		return (0);
	num = 0;
	pnt = 0;
	pow = 10;
	sgn = 1 - 2 * (*s == '-' && s++);
	while (*s != '\0' && pnt <= 1 && (ft_isdigit(*s) || *s == '.'))
	{
		if (ft_isdigit(*s) && pnt < 1)
			num = 10 * num + (*s - '0');
		else if (ft_isdigit(*s) && pnt == 1)
		{
			num += (double)(*s - '0') / pow;
			pow *= 10;
		}
		else if (*s == '.')
			pnt++;
		s++;
	}
	return (num * sgn);
}
