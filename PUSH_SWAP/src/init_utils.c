/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:49:04 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/04 09:16:07 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_ordered(t_push *p)
{
	t_uns	c;

	c = p->n;
	while (c-- > (p->id_a + 1))
		if (*(p->s_a + c) < *(p->s_a + c - 1))
			return (0);
	return (1);
}

void	ft_init_push(int argc, char **argv, t_push *p)
{
	int	cntr;

	cntr = 0;
	p->n = argc;
	p->n_a = p->n;
	p->id_a = 0;
	p->id_b = p->n;
	p->n_b = 0;
	p->mov_n = 0;
	p->pshb = 1;
	while (argc--)
	{
		*(p->s_b + cntr) = NN;
		*(p->s_a + cntr++) = ft_atoi(*(++argv));
	}
}

static short	ft_valid_format(char *str)
{
	char	*tmp;
	int		sgn;

	if (!str || *str == '\0')
		return (0);
	sgn = (*str == '+' || *str == '-');
	if (sgn)
		str++;
	while (*(str + 1) != '\0' && *str == '0')
		str++;
	tmp = str;
	while (*str != '\0')
		if (!ft_isdigit(*str++))
			return (0);
	if (ft_strlen(tmp) == 10)
	{
		if (sgn && ft_strncmp(tmp, "2147483648", 10) > 0)
			return (0);
		else if (!sgn && ft_strncmp(tmp, "2147483647", 10) > 0)
			return (0);
	}
	else if (ft_strlen(tmp) > 10)
		return (0);
	return (1);
}

short	ft_guard_service(int argc, char **av)
{
	int	cn;
	int	nx;

	cn = 1;
	while (cn <= argc)
		if (!ft_valid_format(*(av + cn++)))
			return (0);
	cn = 1;
	while (cn < argc)
	{
		nx = cn + 1;
		while (nx <= argc)
			if (ft_atoi(*(av + cn)) == ft_atoi(*(av + nx++)))
				return (0);
		cn++;
	}
	return (1);
}

void	ft_check_args(int argc, char **argv, t_push *p)
{
	char	**splitted;

	if (argc == 2)
	{
		splitted = ft_split(*(argv + 1), ' ');
		if (splitted)
		{
			argc = ft_arr_len(splitted);
			ft_init_argv(argc, splitted - 1, p);
			ft_free_argv(splitted);
		}
	}
	else if (argc-- > 2)
		ft_init_argv(argc, argv, p);
	else
		exit (0);
}
