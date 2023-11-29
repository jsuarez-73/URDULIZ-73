/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:28:02 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/29 19:28:21 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(long ms)
{
	struct timeval	tday;
	long			start;
	long			now;

	gettimeofday(&tday, NULL);
	start = tday.tv_sec * 1000 + tday.tv_usec / 1000;
	now = start;
	while ((now - start) <= (ms / 1000))
	{
		usleep(500);
		gettimeofday(&tday, NULL);
		now = tday.tv_sec * 1000 + tday.tv_usec / 1000;
	}
}
