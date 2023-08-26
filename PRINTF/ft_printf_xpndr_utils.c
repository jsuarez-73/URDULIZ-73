/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xpndr_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:55:45 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/26 21:12:28 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* lf must be less than tmp*/
/*----------------------START utils CONVERSION-------------------*/
static unsigned int	ft_strlen(char *str)
{
	unsigned int	counter;

	counter = 0;
	while (*str++ != '\0')
		counter++;
	return counter;
}

static unsigned int	ft_numlen(void *n, char type)
{
	u_int	counter;

	counter = 0;
	if (type == '-')
	{
		if (*(int *) n == 0)
			return (1);
		while (*(int *)n != 0)
		{
			*(int *)n = (*(int *)n - *(int *)n % 10) / 10;
			counter++;
		}
	}
	else if ( type == '+')
	{
		if (*(u_int *) n == 0)
			return (1);
		while (*(u_int *) n != 0)
		{
			*(u_int*)n = (*(u_int*)n - *(u_int*)n % 10) / 10;
			counter++;
		}
	}
	return (counter);
}
/*----------------------START wr_mchn CONVERSION-------------------*/
static void	ft_lf_rg(t_wrtr *wr, void (*f)(t_wrtr *, char *))
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

static void	ft_rg_lf(t_wrtr *wr, void (*f)(t_wrtr *, char *))
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

static void	ft_wr_mch(t_wrtr *wr, void (*f)(t_wrtr *, char *))
{
	if (wr->nd->map.minus != 0)
		ft_lf_rg(wr, f);
	else
		ft_rg_lf(wr, f);
}

static int ft_mem_mng(t_nd *nd, u_int dlen, u_int (*m)(t_map, u_int))
{
	u_int	size;
	char	*m_mng;

	size = m(nd->map, dlen);
	m_mng = (char *) malloc(sizeof(char) * size);
	if (m_mng == NULL)
		return (0);
	nd->lf.off = m_mng;
	nd->lf.end = m_mng + size - 1;
	return (1);
}
/*----------------------START str CONVERSION-------------------*/
static void	ft_wr_str(t_wrtr *wr, char *off)
{
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *(wr->end_dt)--;
		else if (wr->nd->map.zero != 0)
			*off = '0';
		else
			*off = 'k';
	}
	else
	{
		if (off <= wr->off + wr->sz - 1)
			*off = *(wr->off_dt)++;
		else if (wr->nd->map.zero != 0)
			*off = '0';
		else
			*off = 'k';
	}
}

static u_int	ft_mng_str(t_map mp, u_int dlen)
{
	u_int size;
	
	if (mp.fnum > mp.pnum)
	{
		if (mp.ppoint != 0)
			size = mp.fnum;
		else
		{
			if (mp.fnum > dlen)
				size = mp.fnum;
			else
				size = dlen;
		}
	}
	else if (mp.pnum <= dlen && mp.ppoint != 0)
		size = mp.pnum;
	else
		size = dlen;
	return (size);
}

static char	*ft_mkstr(t_map mp, char *str, u_int *dlen)
{
	char	*dt;
	u_int	size;

	if (mp.pnum <= *dlen && mp.ppoint != 0)
		size = sizeof(char) * mp.pnum;
	else
		size = sizeof(char) * (*dlen);
	dt = (char *) malloc(size + 1);
	if(dt == NULL)
		return (NULL);
	*dlen = size;
	*(dt + size) = '\0';
	while (size--)
		*(dt + size) = *(str + size);
	return (dt);
}

int ft_str_exp(t_nd *nd, char * str)
{
	t_wrtr	wr;
	void	(*ft_str)(t_wrtr *, char *);
	u_int	(*ft_mstr)(t_map, u_int);
	
	ft_str = ft_wr_str;
	ft_mstr = ft_mng_str;
	wr.nd = nd;
	wr.sz = ft_strlen(str);
	if (ft_mem_mng(nd, wr.sz, ft_mstr) == 0)
		return (0);
	wr.dt = ft_mkstr(nd->map, str, &wr.sz);
	if (wr.dt == NULL)
		return (0);
	ft_wr_mch(&wr, ft_str);
	printf("D:\tDebuggin str: %s\n", nd->lf.off);
	free(wr.dt);
	return (1);
}
/*----------------------START dbl CONVERSION-------------------*/
static u_int	ft_mng_dbl(t_map mp, u_int dlen)
{
	u_int	size;
	int		sgned;

	sgned = 0;
	if (mp.plus != 0 || mp.sgned != 0 || mp.space != 0)
		sgned = 1;
	if (mp.fnum > mp.pnum)
	{
		if (mp.fnum <= dlen)
			size = (dlen + sgned + mp.space);
		else
			size = mp.fnum;
	}
	else if (mp.pnum >= dlen)
		size = mp.pnum + sgned;
	else
		size = dlen + sgned;
	return (size);
}

static char	*ft_mkdbl(int n, unsigned int size)
{
	char		*off_dt;
	char		*end_dt;
	char		dig;

	off_dt = (char *) malloc(size + 1);
	if (off_dt == NULL)
		return (NULL);
	end_dt = off_dt + sizeof(char) * size;
	*end_dt = '\0';
	if (n == 0)
	{
		*(--end_dt) = '0';
		return (end_dt);
	}
	while (n != 0)
	{
		if (n > 0)
			dig = n % 10 + '0';
		else
			dig = '0' - n % 10;
		n = (n - n % 10) / 10;
		*(--end_dt) = dig;
	}
	return (off_dt);
}

static void ft_dbl_vldtns(t_map mp, char *off, t_wrtr *wr, int flag)
{

	if (off == wr->off && mp.sgned != 0)
		*off = '-';
	else if (off == wr->off && mp.plus != 0)
		*off = '+';
	else if (off == wr->off && mp.space != 0)
		*off = ' ';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - wr->sz - flag)
		*off = '0';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - flag)
		*off = *wr->off_dt++;
	else if (mp.pnum < wr->sz && off <= wr->off + wr->sz - flag)
		*off = *wr->off_dt++;
	else
		*off = 'k';
}

static void	ft_dbl_sgnvld(t_map mp, char *off, char *end, char dflt)
{
	if (mp.sgned != 0 && off == end)
		*off = '-';
	else if (mp.plus != 0 && off == end)
		*off = '+';
	else if (mp.space != 0 && off == end)
		*off = 'k';
	else
		*off = dflt;
}

static void	ft_wr_dbl(t_wrtr *wr, char *off)
{
	t_map	mp;

	mp = wr->nd->map;
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *wr->end_dt--;
		else if (mp.zero != 0)
			ft_dbl_sgnvld(mp, off, wr->end, '0');
		else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
			*off = '0';
		else if (mp.pnum > wr->sz)
			ft_dbl_sgnvld(mp, off, wr->off - mp.pnum, 'k');
		else
			ft_dbl_sgnvld(mp, off, wr->off - wr->sz, 'k');
	}
	else
	{
		if (mp.sgned != 0 || mp.plus != 0 || mp.space != 0)
			ft_dbl_vldtns(mp, off, wr, 0);
		else
			ft_dbl_vldtns(mp, off, wr, 1);
	}
}

int ft_dbl_exp(t_nd *nd, int dbl)
{
	int		num;
	t_wrtr	wr;
	u_int	(*ft_mdbl)(t_map, u_int);
	void	(*ft_dbl)(t_wrtr *, char *);

	num = dbl;
	wr.sz = ft_numlen(&num, '-');
	wr.nd = nd;
	if (dbl < 0)
		nd->map.sgned = 1;
	ft_mdbl = ft_mng_dbl;
	ft_dbl = ft_wr_dbl;
	if (ft_mem_mng(nd, wr.sz, ft_mdbl) == 0)
		return (0);
	wr.dt = ft_mkdbl(dbl, wr.sz);
	if (wr.dt == NULL)
		return (0);
	ft_wr_mch(&wr, ft_dbl);
	printf("D:\t Debuggin dbl:%s\t%d\t%d\t%s\n", nd->lf.off, dbl, wr.sz, wr.dt);
	free(wr.dt);
	return (1);
}
/*----------------------START chr CONVERSION-------------------*/
static u_int	ft_mng_chr(t_map mp, u_int size)
{
	if (mp.fnum > size)
		return (mp.fnum);
	else
		return (size);
}

static void	ft_wr_chr(t_wrtr *wr, char *off)
{
	if (off == wr->off)
		*off = *wr->dt;
	else
		*off = ' ';
}

static char	*ft_mkchr(char chr)
{
	char	*dt;

	dt = (char *) malloc(sizeof(char) * 2);
	if (dt == NULL)
		return (NULL);
	*(dt + sizeof(char) * 1) = '\0';
	*dt = chr;
	return (dt);

}
/*Testeado levemente, pero funcional hasta el momento.*/
int ft_chr_exp(t_nd *nd, unsigned char chr)
{
	u_int	(*ft_mchr)(t_map, u_int);
	void	(*ft_chr)(t_wrtr *, char *);
	t_wrtr	wrtr;

	ft_chr = ft_wr_chr;
	ft_mchr = ft_mng_chr;
	wrtr.sz = 1;
	wrtr.nd = nd;
	wrtr.dt = ft_mkchr(chr);
	if (wrtr.dt == NULL)
		return (0);
	if (ft_mem_mng(nd, sizeof(char), ft_mchr) == 0)
		return (0);
	ft_wr_mch(&wrtr, ft_chr);
	printf("D:\t Debuggin chr: %s\t%d\n", nd->lf.off, chr);
	return (0);
}
/*----------------------START int CONVERSION-------------------*/
int ft_int_exp(t_nd *nd, int intg)
{
	int	rtn;
	/*En esta funcion podremos verificar si las funciones como expresiones
	escriben sobre las direcciones de memoria que se le pasan.*/
	rtn = ft_dbl_exp(nd, intg);
	printf("D:\t Debuggin int: %d\t%d\n", nd->is_lf, intg);
	return (rtn);
}
/*----------------------START hex CONVERSION-------------------*/
static u_int	ft_mng_hex(t_map mp, u_int dlen)
{
	u_int	size;
	int		hashed;

	hashed = 0;
	if (mp.hash != 0)
		hashed = 2;
	if (mp.fnum > mp.pnum + hashed)
	{
		if (mp.fnum <= dlen + hashed)
			size = (dlen + hashed);
		else
			size = mp.fnum;
	}
	else if (mp.pnum > dlen)
		size = mp.pnum + hashed;
	else
		size = dlen + hashed;
	return (size);
}

static char	*ft_mkhex(unsigned int hex, int capital)
{
	u_int	num;
	char	*dt;
	u_int	counter;
	char	*tmp;

	counter = 0;
	while (hex >= 16)
	{
		num = hex % 16;
		hex /= 16;
		if (num <= 9)
			num += '0';
		else if (num >= 10 && num <= 16 && capital == 0)
			num = num - 10 + 'a';
		else if (num >= 10 && num <= 16 && capital == 1)
			num = num - 10 + 'A';
		if (counter == 0)
		{
			tmp = (char *) malloc(sizeof(char) * ++counter + 1);
			if (tmp == NULL)
				return (NULL);
			*(tmp + counter) = '\0';
			*tmp = (char) num;
		}
		else
		{
			dt = (char *) malloc(sizeof(char) * ++counter + 1);
			if (dt == NULL)
				return (NULL);
			*(dt + counter) = '\0';
			*dt++ = (char) num;
			while (*tmp != '\0')
				*dt++ = *tmp++;
			dt -= counter;
			free(tmp - counter + 1);
			tmp = dt;
		}
	}
	if (hex <= 9)
		hex += '0';
	else if (hex >= 10 && hex <= 16 && capital == 0)
		hex = hex - 10 + 'a';
	else if (hex >= 10 && hex <= 16 && capital == 1)
		hex = hex - 10 + 'A';
	dt = (char *) malloc(sizeof(char) * ++counter + 1);
	if (dt == NULL)
		return (NULL);
	*(dt + counter) = '\0';
	*dt++ = (char) hex;
	while (*tmp != '\0')
		*dt++ = *tmp++;
	dt -= counter;
	free(tmp - counter + 1);
	return (dt);
}

static void ft_hex_vldtn(char *off, t_wrtr *wr, int flag, int capital)
{
	t_map	mp;

	mp = wr->nd->map;
	if (mp.hash != 0 && off == wr->off)
		*off = '0';
	else if (mp.hash != 0 && off == wr->off + 1 && capital == 0)
		*off = 'x';
	else if (mp.hash != 0 && off == wr->off + 1 && capital == 1)
		*off = 'X';
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum - wr->sz + flag)
		*off = '0';
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum + flag)
		*off = *wr->off_dt++;
	else if (mp.pnum > wr->sz && off >= wr->off + mp.pnum + flag)
		*off = 'k';
	else if (mp.pnum <= wr->sz && off < wr->off + wr->sz + flag)
		*off = *wr->off_dt++;
	else if (mp.pnum <= wr->sz && off >= wr->off + wr->sz + flag)
		*off = 'k';
}

static void	ft_wr_hex(t_wrtr *wr, char *off)
{
	t_map	mp;
/*Falta reducir estas validaciones.*/
	mp = wr->nd->map;
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1)
			*off = *wr->end_dt--;
		else if (mp.zero != 0 && mp.hash != 0 && off > wr->end + 1)
			*off = '0';
		else if (mp.zero != 0 && mp.hash != 0 && off == wr->end + 1)
			*off = 'x';
		else if (mp.zero != 0 && mp.hash != 0 && off == wr->end)
			*off = '0';
		else if (mp.zero != 0 && mp.hash == 0)
			*off = '0';
		else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
			*off = '0';
		else if (mp.pnum > wr->sz && mp.hash != 0 && off == wr->off - mp.pnum)
			*off = 'x';
		else if (mp.pnum > wr->sz && mp.hash != 0 && off == wr->off - mp.pnum - 1)
			*off = '0';
		else if (mp.pnum > wr->sz && mp.hash != 0 && off < wr->off - mp.pnum - 1)
			*off = 'k';
		else if (mp.pnum > wr->sz && mp.hash == 0 && off < wr->off - mp.pnum)
			*off = 'k';
		else if (mp.pnum <= wr->sz && mp.hash != 0 && off == wr->off - wr->sz)
			*off = 'x';
		else if (mp.pnum <= wr->sz && mp.hash != 0 && off == wr->off - wr->sz - 1)
			*off = '0';
		else if (mp.pnum <= wr->sz && mp.hash == 0 && off < wr->off - wr->sz)
			*off = 'k';
		else
			*off = 'k';
	}
	else
	{
		if (mp.hash != 0)
			ft_hex_vldtn(off, wr, 2, 0);
		else
			ft_hex_vldtn(off, wr, 0, 0);

	}
}

int ft_hex_exp(t_nd *nd, unsigned int hex)
{
	t_wrtr	wr;
	u_int	(*ft_mhex)(t_map, u_int);
	void	(*ft_hex)(t_wrtr *, char *);

	ft_mhex = ft_mng_hex;
	ft_hex = ft_wr_hex;
	wr.nd = nd;
	wr.dt = ft_mkhex(hex, 0);
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(nd, wr.sz, ft_mhex) == 0)
		return (0);
	ft_wr_mch(&wr, ft_hex);
	printf("D:\t Debuggin hex: %s\t%d\t%s\n", nd->lf.off, hex, wr.dt);
	return (1);
}

int ft_usgn_exp(t_nd *nd, unsigned int usgn)
{
	/*EL CAST funciona correctamente!*/
	printf("D:\t Debuggin usgn: %d\t%d\n",nd->is_lf, usgn);
	return (0);
}

int ft_chex_exp(t_nd *nd, unsigned int hx)
{
	printf("D:\t Debuggin chex: %d\t%d\n", nd->is_lf, hx);
	return (0);
}

int ft_ptr_exp(t_nd *nd, void * ptr)
{
	printf("D:\t Debuggin ptr: %d\t%p\n", nd->is_lf, ptr);
	return (0);
}

int	ft_per_exp(t_nd *nd)
{
	printf("D:\tDebuggin per %p\n", nd);
	return (0);
}