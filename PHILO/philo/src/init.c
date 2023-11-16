/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:28:26 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/16 13:10:47 by jsuarez-         ###   ########.fr       */
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
	gdt->phs = (t_philo *)malloc(sizeof(t_philo) * n_f);
	ft_init_phs_signals(gdt->phs, gdt->phs + n_f);
	if (!gdt->id || !gdt->phs)
		exit(-1);
	pthread_mutex_init(&gdt->l_start, NULL);
	pthread_mutex_init(&gdt->l_check, NULL);
	pthread_mutex_init(&gdt->l_log, NULL);
	gdt->start = 1;
	gdt->tphe = 0;
	gdt->signal = SIGCONT;
	gdt->markers = n_f;
	gdt->phs->back = gdt->phs + n_f - 1;
}

void	ft_set_philo(t_gdata **gdt, t_philo **phs)
{
	pthread_mutex_lock(&(*gdt)->l_start);
	*phs = (*gdt)->phs + --(*gdt)->markers;
	(*phs)->id = (*gdt)->markers + 1;
	(*phs)->free = FREE;
	(*phs)->ntme = 0;
	(*phs)->ticked = 0;
	(*phs)->timer.t_die = *((*gdt)->params + T_DIE) * MILI_TO_MICRO;
	(*phs)->timer.t_eat = *((*gdt)->params + T_EAT) * MILI_TO_MICRO;
	(*phs)->timer.t_slp = *((*gdt)->params + T_SLP) * MILI_TO_MICRO;
	(*phs)->timer.t_think = (*phs)->timer.t_die / MILI_TO_MICRO;
	(*phs)->state = STARTING;
	(*phs)->signal = &(*gdt)->signal;
	(*phs)->l_start = &(*gdt)->l_start;
	(*phs)->l_log = &(*gdt)->l_log;
	pthread_mutex_init(&(*phs)->fork, NULL);
	pthread_mutex_unlock(&(*gdt)->l_start);
}

static void	ft_set_lifetime(t_gdata *gdt, t_philo *last_phs)
{
	t_philo	*off_phs;

	off_phs = gdt->phs;
	pthread_mutex_lock(&gdt->l_check);
	while (off_phs < last_phs)
	{
		off_phs->timer.l_eat = ft_date_update();
		off_phs++;
	}
	pthread_mutex_unlock(&gdt->l_check);
}

short	ft_wait_all_init(t_gdata *gdt, int n_f)
{
	t_philo			*last_phs;
	t_philo			*phs;

	last_phs = gdt->phs + n_f;
	phs = gdt->phs;
	pthread_mutex_lock(&gdt->l_start);
	while (phs < last_phs)
	{
		if (!phs->signal)
		{
			pthread_mutex_unlock(&gdt->l_start);
			return (1);
		}
		else if (phs + 1 == last_phs && phs->signal)
		{
			ft_set_lifetime(gdt, last_phs);
			gdt->start = 0;
			pthread_mutex_unlock(&gdt->l_start);
			return (0);
		}
		phs++;
	}
	pthread_mutex_unlock(&gdt->l_start);
	return (1);
}
