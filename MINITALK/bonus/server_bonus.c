/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:00:54 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/12 17:56:28 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static t_server	g_server;

void	ft_change_action(enum e_action action)
{
	if (action == PID_ACTION)
	{
		if (sigaction(SIGUSR1, &g_server.pid_act, &g_server.s_act) == -1)
			exit(-1);
		if (sigaction(SIGUSR2, &g_server.pid_act, &g_server.s_act) == -1)
			exit(-1);
	}
	else if (action == STR_ACTION)
	{
		if (sigaction(SIGUSR1, &g_server.s_act, &g_server.pid_act) == -1)
			exit(-1);
		if (sigaction(SIGUSR2, &g_server.s_act, &g_server.pid_act) == -1)
			exit(-1);
	}
}

void	ft_check_buff(void)
{
	*g_server.tmp++ = g_server.chr;
	if (g_server.tmp == g_server.str + SZ_BUF)
	{
		write(1, g_server.str, SZ_BUF - 1);
		g_server.tmp = g_server.str;
	}
	else if (g_server.chr == '\0')
	{
		write(1, g_server.str, ft_strlen(g_server.str));
		ft_change_action(PID_ACTION);
		g_server.tmp = g_server.str;
	}
	g_server.cntr_chr = SZ_CHR;
	g_server.chr = 0;
}

void	ft_char_client(int signum)
{
	if (g_server.cntr_chr--)
	{
		if (signum == SIGUSR1)
		{
			g_server.chr = (g_server.chr | (1 << g_server.cntr_chr));
			kill(g_server.pid_c, SIGUSR2);
		}
		else if (signum == SIGUSR2)
			kill(g_server.pid_c, SIGUSR1);
	}
	if (!g_server.cntr_chr)
		ft_check_buff();
}

void	ft_pid_client(int signum)
{
	static int	cntr;

	if (!cntr)
	{
		cntr = SZ_INT;
		g_server.pid_c = 0;
	}
	if (cntr--)
	{
		if (signum == SIGUSR1)
			g_server.pid_c = (g_server.pid_c | (1 << cntr));
		if (!cntr)
		{
			g_server.s_act.sa_handler = ft_char_client;
			g_server.s_act.sa_mask = g_server.set;
			g_server.s_act.sa_flags = 0;
			ft_change_action(STR_ACTION);
		}
	}
}

int	main(void)
{
	pid_t	pid;

	g_server.tmp = g_server.str;
	g_server.chr = 0;
	g_server.cntr_chr = SZ_CHR;
	sigemptyset(&g_server.set);
	sigaddset(&g_server.set, SIGUSR1);
	sigaddset(&g_server.set, SIGUSR2);
	g_server.pid_act.sa_handler = ft_pid_client;
	g_server.pid_act.sa_mask = g_server.set;
	g_server.pid_act.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &g_server.pid_act, NULL) == -1)
		exit(-1);
	if (sigaction(SIGUSR2, &g_server.pid_act, NULL) == -1)
		exit(-1);
	pid = getpid();
	ft_printf("#SERVER: PID:%d\n", pid);
	while (1)
		pause();
}
