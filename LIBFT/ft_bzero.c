/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:45:02 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/05 16:45:02 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, t_size n)
{
	int	counter;

	counter = 0;
	while (counter < n)
	{
		*(int *)s = '\0';
		counter++;
		s++;
	}
}
