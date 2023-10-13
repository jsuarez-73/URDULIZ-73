/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:02:03 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/12 17:58:28 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H
# include "libft.h"
# include <signal.h>
# ifndef CONST_BONUS
#  define CONST_BONUS
#  define SZ_INT 32
#  define SZ_CHR 8
#  define SZ_PID 32
#  define SZ_BUF 1000
# endif

typedef struct s_server
{
	int					pid_c;
	char				str[SZ_BUF];
	char				*tmp;
	char				chr;
	struct sigaction	s_act;
	struct sigaction	pid_act;
	sigset_t			set;
	t_size				cntr_chr;

}	t_server;

enum e_action
{
	PID_ACTION,
	STR_ACTION
} ;

#endif
