/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:06:28 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/12/01 15:40:44 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_set_supervisor_timer(t_gdata *gdt, t_suptimer *suptimer)
{
	suptimer->now = ft_date_update();
	suptimer->dtime = (suptimer->now - gdt->philo.timer.l_eat) * MILI_TO_MICRO;
	suptimer->phs_tdie = gdt->philo.timer.t_die;
}

static void	*ft_supervisor(void *arg)
{
	t_gdata		*gdt;
	int			n_epme;
	t_suptimer	suptimer;

	gdt = (t_gdata *)arg;
	n_epme = *(gdt->params + N_EPME);
	while (1)
	{
		sem_wait(gdt->s_death);
		ft_set_supervisor_timer(gdt, &suptimer);
		if (n_epme > 0 && gdt->philo.ntme == n_epme)
		{
			sem_post(gdt->s_death);
			break ;
		}
		sem_post(gdt->s_death);
		if (suptimer.dtime >= suptimer.phs_tdie)
		{
			ft_push_log(gdt, "has died", DIED);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

static void	ft_live(t_gdata *gdt, int n_f)
{
	if (n_f > 1)
	{
		sem_wait(gdt->s_table);
		sem_wait(gdt->s_fork);
		sem_wait(gdt->s_fork);
		ft_push_log(gdt, "has taken a fork", FORKING_ONE);
		ft_push_log(gdt, "has taken a fork", FORKING_TWO);
		ft_push_log(gdt, "is eating", EATING);
		sem_wait(gdt->s_death);
		gdt->philo.timer.l_eat = ft_date_update();
		gdt->philo.ntme++;
		sem_post(gdt->s_death);
		sem_post(gdt->s_table);
		ft_usleep(gdt->philo.timer.t_eat);
		sem_post(gdt->s_fork);
		sem_post(gdt->s_fork);
		ft_push_log(gdt, "is sleeping", SLEEPING);
		ft_usleep(gdt->philo.timer.t_slp);
		ft_push_log(gdt, "is thinking", THINKING);
		usleep(500);
	}
}

static short	ft_check_state(t_gdata *gdt, int *state, int n_epme)
{
	if (gdt->philo.state == DIED)
	{
		*state = gdt->philo.state;
		return (0);
	}
	if (n_epme > 0 && gdt->philo.ntme == n_epme)
	{
		gdt->philo.state = FEED;
		*state = FEED;
		return (0);
	}
	return (1);
}

int	ft_born_philo(t_gdata *gdt, int id)
{
	pthread_t	tid;
	int			state;
	int			n_epme;
	int			n_f;

	gdt->philo.id = id;
	gdt->philo.timer.l_eat = ft_date_update();
	state = -1;
	n_epme = *(gdt->params + N_EPME);
	n_f = *(gdt->params + N_PHILO);
	pthread_create(&tid, NULL, ft_supervisor, gdt);
	while (1)
	{
		sem_wait(gdt->s_death);
		if (!ft_check_state(gdt, &state, n_epme))
			break ;
		sem_post(gdt->s_death);
		ft_live(gdt, n_f);
	}
	sem_post(gdt->s_death);
	pthread_join(tid, NULL);
	return (state);
}
