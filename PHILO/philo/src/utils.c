/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:32:54 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/15 19:38:50 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	ft_date_update(void)
{
	struct timeval	tday;

	if (!gettimeofday(&tday, NULL))
		return (tday.tv_sec * 1000 + tday.tv_usec / 1000);
	return (0);
}

static char	*ft_set_emoji(t_state state)
{
	if (state == DIED)
		return (HEADSTONE);
	else if (state == EATING)
		return (SPAGHETTI);
	else if (state == THINKING)
		return (BULB);
	else if (state == SLEEPING)
		return (NAPPING);
	else if (state == FORKING_TWO)
		return (FORK_AND_PLATE);
	else if (state == FORKING_ONE)
		return (FORK);
	return (NULL);
}

void	ft_push_log(t_philo *phs, char *log, t_state state)
{
	suseconds_t	now;
	char		*emoji;
	
	pthread_mutex_lock(phs->l_log);
	now = ft_date_update();
	if (phs->state != state && *phs->signal == SIGCONT)
	{
		phs->state = state;
		if (state == DIED)
			*phs->signal = SIGDIED;
		emoji = ft_set_emoji(state);
		printf("%lu %u %s %s\n", now, phs->id, log, emoji);
	}
	pthread_mutex_unlock(phs->l_log);
}

void	ft_set_locks(t_philo *phs, pthread_mutex_t **f, pthread_mutex_t **s)
{
	if (phs->id % 2 == 0)
	{
		*f = &phs->back->fork;
		*s = &phs->fork;
	}
	else
	{
		*f = &phs->fork;
		*s = &phs->back->fork;
	}
}
