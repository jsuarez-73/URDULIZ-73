/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:45:15 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/12 17:03:44 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include "libft.h"
# include <signal.h>
# ifndef CONST
#  define CONST
#  define SZ_INT 32
#  define SZ_CHR 8
#  define SZ_PID 32
# endif

typedef struct s_client
{
	short				rec;
	struct sigaction	str_act;
	sigset_t			set;
	pid_t				pid_c;
	pid_t				pid_s;

}	t_client;

#endif