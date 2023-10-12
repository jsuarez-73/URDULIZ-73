/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:26:43 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/12 17:32:42 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_client	g_client;

int	ft_check_args(int argc, char **argv, char **str)
{
	if (argc == 3)
	{
		*str = *(argv + 2);
		if (*str == NULL || **str == '\0')
			exit(-1);
		g_client.pid_s = ft_atoi(*(argv + 1));
		if (kill(g_client.pid_s, 0) == -1 || g_client.pid_s == 0)
		{
			ft_printf("#CLIENT: That was a wrong PID\n");
			exit(-1);
		}
		return (1);
	}
	else
	{
		ft_printf("#CLIENT: Less arguments that requeried\n");
		ft_printf("#CLIENT: BNF\n\t./client <pid_srvr> <String>\n");
		ft_printf("\t<pid_srvr> ::= [-|+][0-9]*\n");
		ft_printf("\t<String> ::= [\"][a-zA-Z]*[\"]\n\t\tBy Jesus Suarez\n");
		exit(-1);
	}
}

void	ft_srvr_res(int signum)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		g_client.rec--;
		ft_printf("#CLIENT~%d:\tOK\n", g_client.pid_c);
	}
}

void	ft_str_bits(char c)
{
	short	cntr;

	cntr = SZ_CHR;
	while (cntr--)
	{
		if (((c >> cntr) & 1) == 1)
			kill(g_client.pid_s, SIGUSR1);
		else
			kill(g_client.pid_s, SIGUSR2);
		usleep(10000);
	}
}

void	ft_init_client(void)
{
	t_size	cntr;

	cntr = SZ_PID;
	g_client.pid_c = getpid();
	sigemptyset(&g_client.set);
	sigaddset(&g_client.set, SIGUSR1);
	sigaddset(&g_client.set, SIGUSR2);
	g_client.str_act.sa_handler = ft_srvr_res;
	g_client.str_act.sa_mask = g_client.set;
	g_client.str_act.sa_flags = 0;
	if (sigaction(SIGUSR1, &g_client.str_act, NULL) == -1)
		exit(-1);
	if (sigaction(SIGUSR2, &g_client.str_act, NULL) == -1)
		exit(-1);
	while (cntr--)
	{
		if (((g_client.pid_c >> cntr) & 1) == 1)
			kill(g_client.pid_s, SIGUSR1);
		else
			kill(g_client.pid_s, SIGUSR2);
		usleep(5000);
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	t_size	len;

	if (ft_check_args(argc, argv, &str))
	{
		len = ft_strlen(str) + 1;
		ft_init_client();
		while (len)
		{
			if (!g_client.rec)
			{
				len--;
				g_client.rec = SZ_CHR;
				ft_str_bits(*str);
				str++;
			}
		}
	}
	exit(0);
}
