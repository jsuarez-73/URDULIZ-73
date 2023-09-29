/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xpndr_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:55:45 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/21 20:10:10 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

unsigned int	ft_strlen_p(char *str)
{
	unsigned int	counter;

	counter = 0;
	if (str == NULL)
		return (0);
	while (*str++ != '\0')
		counter++;
	return (counter);
}

char	*ft_mem_asgn(char **tmp, char **dt, long num, t_uns *counter)
{
	if (*counter == 0)
	{
		*tmp = (char *) malloc(sizeof(char) * ++(*counter) + 1);
		if (*tmp == NULL)
			return (NULL);
		*(*tmp + *counter) = '\0';
		**tmp = (char) num;
		*dt = *tmp;
		return (*dt);
	}
	*tmp = (char *) malloc(sizeof(char) * ++(*counter) + 1);
	if (*tmp == NULL)
	{
		free(*dt);
		return (NULL);
	}
	*(*tmp + *counter) = '\0';
	*(*tmp)++ = (char) num;
	while (**dt != '\0')
		*(*tmp)++ = *(*dt)++;
	*tmp -= *counter;
	free(*dt - *counter + 1);
	*dt = *tmp;
	return (*dt);
}

int	ft_mem_mng_p(t_wrtr *wr, t_uns (*m)(t_wrtr *))
{
	t_uns	size;
	char	*m_mng;
	t_nd	*nd;

	nd = wr->nd;
	size = m(wr);
	if (size != 0)
		m_mng = (char *) malloc(sizeof(char) * size);
	else
		return (0);
	if (m_mng == NULL)
		return (0);
	nd->lf.off = m_mng;
	nd->lf.end = m_mng + size - 1;
	return (1);
}

char	*ft_mkhex(unsigned long hex, t_caphex capital)
{
	unsigned long	num;
	char			*dt;
	t_uns			counter;
	char			*tmp;

	counter = 0;
	dt = NULL;
	if (hex == 0)
	{
		if (ft_mem_asgn(&tmp, &dt, '0', &counter) == NULL)
			return (NULL);
		return (dt);
	}
	while (hex > 0)
	{
		num = hex % 16;
		hex /= 16;
		if (num <= 9)
			num += '0';
		else if (num >= 10 && num <= 16)
			num = num - 10 + capital;
		if (ft_mem_asgn(&tmp, &dt, num, &counter) == NULL)
			return (NULL);
	}
	return (dt);
}

char	*ft_mkdbl(t_uns n)
{
	t_uns	num;
	char	*dt;
	t_uns	counter;
	char	*tmp;

	counter = 0;
	if (n == 0)
	{
		if (ft_mem_asgn(&tmp, &dt, '0', &counter) == NULL)
			return (NULL);
		else
			return (dt);
	}
	while (n > 0)
	{
		num = n % 10 + '0';
		n /= 10;
		if (ft_mem_asgn(&tmp, &dt, num, &counter) == NULL)
			return (NULL);
	}
	return (dt);
}
