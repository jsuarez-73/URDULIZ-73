/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xpndr_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:55:45 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/02 21:14:56 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Colocar la cantidad de funciones que no sobrepasen el limite maximo de 5 per file.*/
unsigned int	ft_strlen(char *str)
{
	unsigned int	counter;

	counter = 0;
	while (*str++ != '\0')
		counter++;
	return (counter);
}

char	*ft_mem_asgn(char **tmp, char **dt, long num, u_int *counter)
{
	if (*counter == 0)
	{
		*tmp = (char *) malloc(sizeof(char) * ++(*counter) + 1);
		if (*tmp == NULL)
			return (NULL);
		*(*tmp + *counter) = '\0';
		**tmp = (char) num;
		*dt = *tmp;
	}
	else
	{
		*tmp = (char *) malloc(sizeof(char) * ++(*counter) + 1);
		if (*tmp == NULL)
			return (NULL);
		*(*tmp + *counter) = '\0';
		*(*tmp)++ = (char) num;
		while (**dt != '\0')
			*(*tmp)++ = *(*dt)++;
		*tmp -= *counter;
		free(*dt - *counter + 1);
		*dt = *tmp;
	}
	return (*dt);
}

void	ft_lf_rg(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	char	*off;
	char	*end;

	off = wr->nd->lf.off;
	end = wr->nd->lf.end;
	wr->off_dt = wr->dt;
	wr->end_dt = wr->dt + wr->sz - 1;
	wr->end = end;
	wr->off = off;
	wr->rg_lf = 0;
	while (off <= end)
		f(wr, off++);
}

void	ft_rg_lf(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	char	*off;
	char	*end;

	off = wr->nd->lf.off;
	end = wr->nd->lf.end;
	wr->off_dt = wr->dt;
	wr->end_dt = wr->dt + wr->sz - 1;
	wr->end = off;
	wr->off = end;
	wr->rg_lf = 1;
	while (end >= off)
	{
		f(wr, end--);
	}
}

void	ft_wr_mch(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	if (wr->nd->map.minus != 0)
		ft_lf_rg(wr, f);
	else
		ft_rg_lf(wr, f);
}

int ft_mem_mng(t_wrtr *wr, u_int (*m)(t_wrtr *))
{
	u_int	size;
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

char	*ft_mkhex(long hex, t_caphex capital)
{
	long	num;
	char	*dt;
	u_int	counter;
	char	*tmp;

	counter = 0;
	if (hex == 0)
	{
		if (ft_mem_asgn(&tmp, &dt, '0', &counter) == NULL)
			return (NULL);
		else
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
