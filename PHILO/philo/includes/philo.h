/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:50 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/14 17:27:05 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ARGS 5
# include <unistd.h> //usleep, write
# include <pthread.h> //threads functions
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# define MILI_TO_MICRO 1000 //convert milisecs to microsecs
# ifndef EMOJIS
# define EMOJIS
#  define FORK "\U0001F374"
#  define SPAGHETTI "\U0001F35D"
#  define BULB "\U0001F4A1"
#  define HEADSTONE "\U0001FAA6"
#  define NAPPING "\U0001F4A4"
#  define FORK_AND_PLATE "\U0001F37D \U0000FE0F"
# endif
enum	e_param
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLP,
	N_EPME
} ;

typedef enum	e_lock
{
	BUSY,
	FREE
}	t_lock;

typedef enum	e_signal
{
	SIGCONT,
	SIGDIED,
	SIGNTME
}	t_signal;

typedef enum	e_state
{
	STARTING,
	FORKING_ONE,
	FORKING_TWO,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef struct	s_timers
{
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				t_think;
	suseconds_t		l_eat;
}	t_timers;

typedef struct	s_philo
{
	t_timers		timer;
	unsigned int	id;
	int				ntme;
	t_lock			free;
	t_state			state;
	t_signal		*signal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*l_start;
	pthread_mutex_t	*l_log;
	struct s_philo	*back;
}	t_philo;

typedef struct	s_gdata
{
	short				start;
	int					params[ARGS];
	unsigned int		markers;
	int					tphe;
	t_signal			signal;
	t_philo				*phs;
	pthread_t			*id;
	pthread_mutex_t		l_start;
	pthread_mutex_t		l_check;
	pthread_mutex_t		l_log;
}	t_gdata;

void	ft_init_args(int argc, char **argv, int *params);

#endif