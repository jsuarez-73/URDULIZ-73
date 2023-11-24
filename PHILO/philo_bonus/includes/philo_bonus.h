/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:49:45 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/24 20:57:40 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define ARGS 5
# include <unistd.h> //usleep, write, pid_t fork(void)
# include <pthread.h> //threads functions
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <sys/wait.h> // pid_t waitpid(pid, int *stat_loc, int options)
# include <fcntl.h> /* For O_* constants */
# include <sys/stat.h> /* For mode constants */
# include <semaphore.h> //sem_open, sem_close, sem_post, sem_wait, sem_unlink
# include <signal.h> //kill(pid, signal)
# define MILI_TO_MICRO 1000 //convert milisecs to microsecs
# ifndef NAMES
#  define NAMES
#  define SEM_FORK "/sfork"
#  define SEM_DEATH "/sdeath"
#  define SEM_STOP "/sstop"
#  define SEM_TERM "/sterm"
#  define SEM_TABLE "/stable"
#  define NCH_SD 7
# endif
# ifndef EMOJIS
#  define EMOJIS
#  define FORK "\U0001F374"
#  define SPAGHETTI "\U0001F35D"
#  define BULB "\U0001F4A1"
#  define HEADSTONE "\U0001FAA6"
#  define NAPPING "\U0001F4A4"
#  define FORK_AND_PLATE "\U0001F37D \U0000FE0F"
# endif

enum	e_tproc
{
	CHILD,
	PARENT
} ;

enum	e_param
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLP,
	N_EPME
} ;

enum	e_sem_close
{
	NO_FLUSH = 0,
	F_FORK = 1,
	F_DEATH = 2,
	F_STOP = 4,
	F_TERM = 8,
	F_TABLE = 16,
	FE_NFLUSH = 32,
	FLUSH_ALL = (F_DEATH | F_STOP | F_FORK | F_TERM | F_TABLE)
} ;

enum	e_semcls
{
	CLOSE = 1,
	UNLINK = 2,
	CLS_UNLINK = (CLOSE | UNLINK)
} ;

typedef enum e_state
{
	FEED,
	DIED,
	WAITING,
	RUNNING,
	FORKING_ONE,
	FORKING_TWO,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_suptimer
{
	suseconds_t	now;
	suseconds_t	dtime;
	int			phs_tdie;
}	t_suptimer;

typedef struct s_timers
{
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				t_think;
	suseconds_t		l_eat;
}	t_timers;

typedef struct s_philo
{
	t_timers		timer;
	int				ntme;
	int				id;
	t_state			state;
}	t_philo;

typedef struct s_gdata
{
	int			params[ARGS];
	pid_t		*id;
	int			tphe;
	short		death;
	char		**s_names;
	pthread_t	id_death;
	sem_t		*s_fork;
	sem_t		**s_death;
	sem_t		*s_stop;
	sem_t		*s_term;
	sem_t		*s_table;
	t_philo		philo;
}	t_gdata;

void	ft_init_args(int argc, char **argv, int *params);

#endif