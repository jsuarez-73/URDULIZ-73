/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:01:44 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/24 21:21:14 by jsuarez-         ###   ########.fr       */
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

suseconds_t	ft_date_update(void)
{
	struct timeval	tday;

	if (!gettimeofday(&tday, NULL))
		return (tday.tv_sec * 1000 + tday.tv_usec / 1000);
	return (0);
}

char	*ft_set_emoji(t_state state)
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
