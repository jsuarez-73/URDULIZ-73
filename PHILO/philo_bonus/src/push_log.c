/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:17:33 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/12/01 16:00:10 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_push_log(t_gdata *gdt, char *log, t_state state)
{
	long	now;
	char	*emoji;

	sem_wait(gdt->s_death);
	if (gdt->philo.state == DIED)
	{
		sem_post(gdt->s_death);
		return ;
	}
	now = ft_date_update();
	if (gdt->philo.state != state && gdt->philo.state != FEED)
	{
		gdt->philo.state = state;
		emoji = ft_set_emoji(state);
		sem_post(gdt->s_death);
		sem_wait(gdt->s_term);
		printf("%ld %u %s %s\n", now, gdt->philo.id, log, emoji);
		if (state != DIED)
			sem_post(gdt->s_term);
	}
	else
		sem_post(gdt->s_death);
}
