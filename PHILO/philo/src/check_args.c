/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:13:55 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/16 12:01:28 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *s1)
{	
	int		num;
	short	sgn;

	num = 0;
	sgn = 1;
	while (*s1 == ' ' || *s1 == '\n' || *s1 == '\f' || *s1 == '\t'
		|| *s1 == '\v' || *s1 == '\r')
		s1++;
	if (*s1 == '-' || *s1 == '+')
	{
		if (*s1 == '-')
			sgn = -1;
		s1++;
	}
	while (ft_isdigit((int) *s1))
		num = (num * 10) + (*s1++ - '0');
	return (num * sgn);
}

static int	ft_valid_format(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

static int	ft_guard_checker(int argc, char **argv)
{
	while (argc-- > 1)
		if (!ft_valid_format(*(argv + argc)))
			return (0);
	return (1);
}

void	ft_init_args(int argc, char **argv, int *params)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_guard_checker(argc, argv))
		{
			if (argc == 5)
				*(params + argc - 1) = 0;
			while (argc-- > 1)
				*(params + argc - 1) = ft_atoi(*(argv + argc));
			if (*(params + argc) == 0)
			{
				printf("Who are gonna eat all that food mate, uh?\n");
				exit(-1);
			}
		}
		else
		{
			printf("Arguments with invalid format\n");
			exit(-1);
		}
	}
	else
	{
		printf("Allowed arguments min: 4 max:5\n");
		exit(-1);
	}
}
