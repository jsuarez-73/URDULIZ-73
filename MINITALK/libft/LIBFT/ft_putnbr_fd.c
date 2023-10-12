/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:57:51 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/20 18:07:50 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	t_size	pow;

	num = (long) n;
	pow = 1;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
		n *= -1;
	}
	if (num == 0)
		ft_putchar_fd('0', fd);
	while (n != 0)
	{
		pow *= 10;
		n = (n - (n % 10)) / 10;
	}
	while (pow != 1)
	{
		ft_putchar_fd((num * 10 / pow) + '0', fd);
		num -= (num * 10 / pow) * (pow / 10);
		pow /= 10;
	}
}
