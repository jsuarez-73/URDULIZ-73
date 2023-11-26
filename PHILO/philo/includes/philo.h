/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:50 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/26 19:31:12 by jsuarez-         ###   ########.fr       */
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
#  define EMOJIS
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

typedef enum e_lock
{
	BUSY,
	FREE
}	t_lock;

typedef enum e_signal
{
	SGCONT,
	SIGDIED,
	SIGNTME
}	t_signal;

typedef enum e_state
{
	STARTING,
	FORKING_ONE,
	FORKING_TWO,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef struct s_timers
{
	long	t_die;
	long	t_slp;
	long	t_eat;
	long	t_think;
	long	l_eat;
}	t_timers;

typedef struct s_philo
{
	t_timers		timer;
	unsigned int	id;
	int				ntme;
	short			ticked;
	int				round;
	short			feed;
	int				*tables;
	t_lock			free;
	t_state			state;
	t_signal		*signal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*l_shared;
	struct s_philo	*back;
}	t_philo;

typedef struct s_gdata
{
	short				start;
	int					params[ARGS];
	unsigned int		markers;
	int					tphe;
	int					tables;
	int					phs_feed;
	t_signal			signal;
	t_philo				*phs;
	pthread_t			*id;
	pthread_t			super;
	pthread_mutex_t		l_shared;
}	t_gdata;

void		ft_init_args(int argc, char **argv, int *params);
void		ft_init_gdata(t_gdata *gdt, int n_f);
void		ft_set_philo(t_gdata **gdt, t_philo **phs);
short		ft_wait_all_init(t_gdata *gdt, int n_f);
void		*ft_life_philo(void *arg);
void		ft_set_locks(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s);
void		ft_push_log(t_philo *phs, char *log, t_state state);
long		ft_date_update(void);
void		ft_memory_flush(t_gdata *gdt);
void		ft_create_threads(t_gdata *gdt, int n_f);
void		ft_join_threads(t_gdata *gdt, int n_f);
short		ft_all_lifes(t_gdata *gdt, t_philo *phs);

#endif