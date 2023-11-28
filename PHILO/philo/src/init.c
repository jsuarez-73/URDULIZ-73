/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:28:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/28 16:02:39 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_phs_signals(t_philo *phs, t_philo *last_phs)
{
	while (phs < last_phs)
	{
		phs->signal = NULL;
		phs++;
	}
}

void	ft_init_gdata(t_gdata *gdt, int n_f)
{
	gdt->id = (pthread_t *)malloc(sizeof(pthread_t) * (n_f));
	if (!gdt->id)
		exit(-1);
	gdt->phs = (t_philo *)malloc(sizeof(t_philo) * n_f);
	if (!gdt->phs)
	{
		free(gdt->id);
		exit(-1);
	}
	ft_init_phs_signals(gdt->phs, gdt->phs + n_f);
	pthread_mutex_init(&gdt->l_shared, NULL);
	gdt->start = 1;
	gdt->tphe = 0;
	gdt->signal = SGCONT;
	gdt->markers = n_f;
	gdt->phs->back = gdt->phs + n_f - 1;
	gdt->tables = n_f - 1;
	gdt->phs_feed = 0;
}

void	ft_set_philo(t_gdata **gdt, t_philo **phs)
{
	pthread_mutex_lock(&(*gdt)->l_shared);
	*phs = (*gdt)->phs + --(*gdt)->markers;
	(*phs)->id = (*gdt)->markers + 1;
	(*phs)->free = FREE;
	(*phs)->ntme = 0;
	(*phs)->ticked = 0;
	(*phs)->timer.t_die = *((*gdt)->params + T_DIE) * MILI_TO_MICRO;
	(*phs)->timer.t_eat = *((*gdt)->params + T_EAT) * MILI_TO_MICRO;
	(*phs)->timer.t_slp = *((*gdt)->params + T_SLP) * MILI_TO_MICRO;
	(*phs)->state = STARTING;
	(*phs)->signal = &(*gdt)->signal;
	(*phs)->l_shared = &(*gdt)->l_shared;
	(*phs)->feed = 0;
	(*phs)->round = 0;
	(*phs)->tables = &(*gdt)->tables;
	pthread_mutex_init(&(*phs)->fork, NULL);
	pthread_mutex_unlock(&(*gdt)->l_shared);
}

static void	ft_set_lifetime(t_gdata *gdt, t_philo *last_phs)
{
	t_philo	*off_phs;

	off_phs = gdt->phs;
	while (off_phs < last_phs)
	{
		off_phs->timer.l_eat = ft_date_update();
		off_phs++;
	}
}

short	ft_wait_all_init(t_gdata *gdt, int n_f)
{
	t_philo			*last_phs;
	t_philo			*phs;

	last_phs = gdt->phs + n_f;
	phs = gdt->phs;
	pthread_mutex_lock(&gdt->l_shared);
	while (phs < last_phs)
	{
		if (!phs->signal)
		{
			pthread_mutex_unlock(&gdt->l_shared);
			return (1);
		}
		else if (phs + 1 == last_phs && phs->signal)
		{
			ft_set_lifetime(gdt, last_phs);
			gdt->start = 0;
			pthread_mutex_unlock(&gdt->l_shared);
			return (0);
		}
		phs++;
	}
	pthread_mutex_unlock(&gdt->l_shared);
	return (1);
}
