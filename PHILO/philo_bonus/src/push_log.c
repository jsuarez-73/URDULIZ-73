/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:17:33 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/25 12:09:40 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_push_log(t_gdata *gdt, char *log, t_state state)
{
	long	now;
	char	*emoji;

	sem_wait(*(gdt->s_death + gdt->philo.id - 1));
	if (gdt->philo.state == DIED)
	{
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
		return ;
	}
	now = ft_date_update();
	if (gdt->philo.state != state && gdt->philo.state != FEED)
	{
		gdt->philo.state = state;
		emoji = ft_set_emoji(state);
		sem_wait(gdt->s_term);
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
		printf("%ld %u %s %s\n", now, gdt->philo.id, log, emoji);
		if (state != DIED)
			sem_post(gdt->s_term);
	}
	else
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
}
