/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:17:44 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/24 17:19:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_ndigits(int n)
{
	int	cn;

	cn = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = (n - n % 10) / 10;
		cn++;
	}
	return (cn);
}

void	ft_set_name(char *spot, int ndig, int id)
{
	int	cn;
	int	dig;

	cn = (NCH_SD + ndig);
	*(spot + (NCH_SD + ndig)) = '\0';
	while (cn--)
	{
		if (cn < NCH_SD)
			*(spot + cn) = *(SEM_DEATH + cn);
		else
		{
			if (id >= 10)
			{
				dig = id % 10;
				id = (id - dig) / 10;
			}
			else
				dig = id;
			*(spot + cn) = dig + '0';
		}
	}
}

void	ft_unlink_sdeaths(t_gdata *gdt, int n_f)
{
	int	cn;
	int	res;

	cn = -1;
	res = 0;
	while (++cn < n_f && res == 0)
		res = sem_unlink(*(gdt->s_names + cn));
}

int	ft_open_semaphores(t_gdata *gdt)
{
	int	o_flags;
	int	cn;
	int n_f;

	cn = *(gdt->params + N_PHILO);
	n_f = cn;
	o_flags = O_CREAT | O_EXCL;
	sem_unlink(SEM_FORK);
	ft_unlink_sdeaths(gdt, n_f);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_TERM);
	sem_unlink(SEM_TABLE);
	gdt->s_fork =  sem_open(SEM_FORK, o_flags, 0664, n_f);
	if (gdt->s_fork == SEM_FAILED)
		return (FE_NFLUSH);
	while (cn--)
	{
		*(gdt->s_death + cn) =  sem_open(*(gdt->s_names + cn), o_flags, 0664, 1);
		if (*(gdt->s_death + cn) == SEM_FAILED)
		{
			while (++cn < n_f)
			{
				sem_close(*(gdt->s_death + cn));
				sem_unlink(*(gdt->s_names + cn));
			}
			return (F_FORK);
		}
	}
	gdt->s_stop = sem_open(SEM_STOP, o_flags, 0664, 1);
	if (gdt->s_stop == SEM_FAILED)
		return (F_FORK | F_DEATH);
	gdt->s_term = sem_open(SEM_TERM, o_flags, 0664, 1);
	if (gdt->s_term == SEM_FAILED)
		return (F_FORK | F_DEATH | F_STOP);
	gdt->s_table = sem_open(SEM_TABLE, o_flags, 0664, n_f / 2);
	if (gdt->s_table == SEM_FAILED)
		return (F_FORK | F_DEATH | F_STOP | F_TERM);
	return (NO_FLUSH);
}

void	ft_close_semaphores(t_gdata *gdt, int cls_mask, int flush_mask)
{
	int	cn;
	int	xn;

	cn = *(gdt->params + N_PHILO);
	xn = cn;
	if (flush_mask & FE_NFLUSH)
		return ;
	if ((flush_mask & F_FORK) && (cls_mask & CLOSE))
		sem_close(gdt->s_fork);
	if ((flush_mask & F_FORK) && (cls_mask & UNLINK))
		sem_unlink(SEM_FORK);
	if ((flush_mask & F_DEATH) && (cls_mask & CLOSE))
	{
		while (cn--)
			sem_close(*(gdt->s_death + cn));
	}
	if ((flush_mask & F_DEATH) && (cls_mask & UNLINK))
		while (xn--)
			sem_unlink(*(gdt->s_names + xn));
	if ((flush_mask & F_STOP) && (cls_mask & CLOSE))
		sem_close(gdt->s_stop);
	if ((flush_mask & F_STOP) && (cls_mask & UNLINK))
		sem_unlink(SEM_STOP);
	if ((flush_mask & F_TERM) && (cls_mask & CLOSE))
		sem_close(gdt->s_term);
	if ((flush_mask & F_TERM) && (cls_mask & UNLINK))	
		sem_unlink(SEM_TERM);
	if ((flush_mask & F_TABLE) && (cls_mask & CLOSE))
		sem_close(gdt->s_table);
	if ((flush_mask & F_TABLE) && (cls_mask & UNLINK))	
		sem_unlink(SEM_TABLE);
}

char	**ft_set_semaphore_names(int n_f)
{
	char	**names;
	int		ndig;
	int		cn;

	cn = n_f;
	names = (char **)malloc(sizeof(char *) * n_f);
	if (!names)
		return (NULL);
	while (cn--)
	{
		ndig = ft_ndigits(cn);
		*(names + cn) = (char *)malloc(ndig + NCH_SD + 1);
		if (!*(names + cn))
		{
			while (++cn < n_f)
				free(*(names + cn));
			free(names);
			return (NULL);
		}
		ft_set_name(*(names + cn), ndig, cn);
	}
	return (names);
}

short	ft_init_gdata(t_gdata *gdt, int n_f)
{
	int	flush_mask;

	flush_mask = NO_FLUSH;
	gdt->tphe = 0;
	gdt->death = 0;
	gdt->philo.timer.t_die = *(gdt->params + T_DIE) * MILI_TO_MICRO;
	gdt->philo.timer.t_slp = *(gdt->params + T_SLP) * MILI_TO_MICRO;
	gdt->philo.timer.t_eat = *(gdt->params + T_EAT) * MILI_TO_MICRO;
	gdt->philo.timer.t_think = gdt->philo.timer.t_die / MILI_TO_MICRO;
	gdt->philo.timer.l_eat = 0;
	gdt->philo.ntme = 0;
	gdt->philo.state = WAITING;
	gdt->philo.id = 0;
	gdt->id = (pid_t *)malloc(sizeof(pid_t) * n_f);
	if (!gdt->id)
		return (0);
	gdt->s_death = (sem_t **)malloc(sizeof(sem_t *) * n_f);
	if (!gdt->s_death)
		return (0);
	gdt->s_names = ft_set_semaphore_names(n_f);
	if (!gdt->s_names)
		return (0);
	flush_mask = ft_open_semaphores(gdt);
	if (flush_mask)
	{
		ft_close_semaphores(gdt, CLS_UNLINK, flush_mask);
		free(gdt->id);
		free(gdt->s_death);
		free(gdt->s_names);
		return (0);
	}
	return (1);
}

void	ft_exit(t_gdata *gdt, int status, int parent)
{
	int	cn;

	cn = *(gdt->params + N_PHILO);
	if (parent)
		ft_close_semaphores(gdt, CLS_UNLINK, FLUSH_ALL);
	else
	{
		ft_close_semaphores(gdt, CLOSE, FLUSH_ALL);
	}
	if (gdt->id)
		free(gdt->id);
	if (gdt->s_death)
		free(gdt->s_death);
	if (gdt->s_names)
	{
		while (cn--)
			free(*(gdt->s_names + cn));
		free(gdt->s_names);
	}
	exit(status);
}

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

void	ft_push_log(t_gdata *gdt, char *log, t_state state)
{
	suseconds_t	now;
	char		*emoji;

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
		printf("%lu %u %s %s\n", now, gdt->philo.id, log, emoji);
		if (state != DIED)
			sem_post(gdt->s_term);
	}
	else
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
}

void	*ft_supervisor(void *arg)
{
	t_gdata		*gdt;
	suseconds_t	now;
	suseconds_t	dtime;
	int			n_epme;
	int			phs_tdie;

	gdt = (t_gdata *)arg;
	n_epme = *(gdt->params + N_EPME);
	while (1)
	{
		sem_wait(*(gdt->s_death + gdt->philo.id - 1));
		now = ft_date_update();
		dtime = (now - gdt->philo.timer.l_eat) * MILI_TO_MICRO;
		phs_tdie = gdt->philo.timer.t_die;
		if (n_epme > 0 && gdt->philo.ntme == n_epme)
		{
			sem_post(*(gdt->s_death + gdt->philo.id - 1));
			break;
		}
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
		if (dtime >= phs_tdie)
		{
			ft_push_log(gdt, "has died", DIED);
			break;
		}
		usleep(1);
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
		sem_wait(*(gdt->s_death + gdt->philo.id - 1));
		gdt->philo.timer.l_eat = ft_date_update();
		gdt->philo.ntme++;
		sem_post(*(gdt->s_death + gdt->philo.id - 1));
		sem_post(gdt->s_table);
		usleep(gdt->philo.timer.t_eat);
		sem_post(gdt->s_fork);
		sem_post(gdt->s_fork);
		ft_push_log(gdt, "is sleeping", SLEEPING);
		usleep(gdt->philo.timer.t_slp);
		ft_push_log(gdt, "is thinking", THINKING);
		usleep(gdt->philo.timer.t_think);
	}
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
		sem_wait(*(gdt->s_death + id - 1));
		if (gdt->philo.state == DIED)
		{
			state = gdt->philo.state;
			break;
		}
		if (n_epme > 0 && gdt->philo.ntme == n_epme)
		{
			gdt->philo.state = FEED;
			break;
		}
		sem_post(*(gdt->s_death + id - 1));
		ft_live(gdt, n_f);
	}
	sem_post(*(gdt->s_death + id - 1));
	pthread_join(tid, NULL);
	return (state);
}

short	ft_create_childs(t_gdata *gdt, int n_f)
{
	pid_t	ppid;
	int		cn;
	int		id;

	cn = -1;
	id = 1;
	while (++cn < n_f)
	{
		ppid = fork();
		if (ppid)
		{
			id++;
			*(gdt->id + cn) = ppid;
		}
		else if (ppid == -1)
			return (0);
		else
			ft_exit(gdt, ft_born_philo(gdt, id), 0);
	}
	return (1);
}

void	*ft_super_death(void *arg)
{
	t_gdata	*gdt;
	int		cn;

	gdt = (t_gdata*)arg;
	cn = -1;
	while (1)
	{
		sem_wait(gdt->s_stop);
		if (gdt->death)
		{
			while (++cn < *(gdt->params + N_PHILO))
				kill(*(gdt->id + cn), SIGKILL);
			break;
		}
		else
		{
			if (gdt->tphe == *(gdt->params + N_PHILO))
				break;
		}
		sem_post(gdt->s_stop);
		usleep(1);
	}
	sem_post(gdt->s_stop);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_gdata	gdt;
	int		n_f;
	int		status;

	ft_init_args(argc, argv, gdt.params);
	n_f = *(gdt.params + N_PHILO);
	if (!ft_init_gdata(&gdt, n_f))
		exit(-1);
	if (!ft_create_childs(&gdt, n_f))
		ft_exit(&gdt, -1, 1);
	pthread_create(&gdt.id_death, NULL, ft_super_death, &gdt);
	while (n_f--)
	{
		waitpid(-1, &status, 0);
		sem_wait(gdt.s_stop);
		if (!status)
			gdt.tphe++;
		else
			gdt.death++;
		sem_post(gdt.s_stop);
	}
	pthread_join(gdt.id_death, NULL);
	ft_exit(&gdt, 0, 1);
	return (0);
}

