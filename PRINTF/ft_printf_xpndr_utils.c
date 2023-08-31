/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xpndr_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:55:45 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/08/31 19:51:49 by jsuarez-         ###   ########.fr       */
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
	return (counter);
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

static int ft_mem_mng(t_wrtr *wr, u_int (*m)(t_wrtr *))
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

static u_int	ft_mng_str(t_wrtr *wr)
{
	t_map	mp;
	
	mp = wr->nd->map;
	if (mp.fnum > mp.pnum)
	{
		if (mp.ppoint != 0)
			return (mp.fnum);
		else
		{
			if (mp.fnum > wr->sz)
				return (mp.fnum);
			else
				return (wr->sz);
		}
	}
	else if (mp.pnum <= wr->sz && mp.ppoint != 0)
		return (mp.pnum);
	else
		return (wr->sz);
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

int ft_str_exp(t_nd *nd, char *str)
{
	t_wrtr			wr;
	void			(*ft_str)(t_wrtr *, char *);
	unsigned int	(*ft_mstr)(t_wrtr *);
	
	ft_str = ft_wr_str;
	ft_mstr = ft_mng_str;
	wr.nd = nd;
	wr.sz = ft_strlen(str);
	wr.d = str;
	if (ft_mem_mng(&wr, ft_mstr) == 0)
		return (0);
	wr.dt = ft_mkstr(nd->map, str, &wr.sz);
	if (wr.dt == NULL)
		return (0);
	ft_wr_mch(&wr, ft_str);
	printf("D:\t Debuggin str: %s\n", nd->lf.off);
	free(wr.dt);
	return (1);
}
/*----------------------START dbl CONVERSION-------------------*/
static u_int	ft_mng_dbl(t_wrtr *wr)
{
	t_map	mp;
	int		sgned;
	int		exp;

	sgned = 0;
	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (mp.plus != 0 || mp.sgned != 0 || mp.space != 0)
		sgned = 1;
	if (exp && mp.fnum >= 1)
		return (mp.fnum);
	else if (exp && mp.fnum < 1)
		return (sgned);
	else if (mp.fnum > mp.pnum)
	{
		if (mp.fnum <= wr->sz)
			return (wr->sz + sgned);
		else
			return (mp.fnum);
	}
	else if (mp.pnum >= wr->sz)
		return (mp.pnum + sgned);
	else
		return (wr->sz + sgned);
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

/*Con pocas pruebas parece estar parcheado el script*/
static void ft_dbl_vldtns(t_map mp, char *off, t_wrtr *wr, int f)
{
	int	exp;

	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (off == wr->off && mp.sgned != 0)
		*off = '-';
	else if (off == wr->off && mp.plus != 0)
		*off = '+';
	else if (off == wr->off && mp.space != 0)
		*off = 'k';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - wr->sz - f)
		*off = '0';
	else if (mp.pnum > wr->sz && off <= wr->off + mp.pnum - f)
		*off = *wr->off_dt++;
	else if (mp.pnum < wr->sz && off <= wr->off + wr->sz - f && !exp)
		*off = *wr->off_dt++;
	else
		*off = 'k';
}
/*Presuntamente esta parcheado rg_lf del script teniendo en cuenta la precision 0 con dbl 0*/
static void	ft_dbl_sgnvld(t_wrtr *wr, char *off, char *end, char dflt)
{
	int		exp;
	t_map	mp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (mp.sgned != 0 && off == end && !exp)
		*off = '-';
	else if (mp.plus != 0 && off == end && !exp)
		*off = '+';
	else if (mp.space != 0 && off == end && !exp)
		*off = 'k';
	else if (exp && mp.plus != 0 && off == wr->off)
		*off = '+';
	else
		*off = dflt;
}

static void	ft_wr_dbl(t_wrtr *wr, char *off)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (mp.ppoint != 0 && mp.pnum == 0 && *(int *) wr->d == 0);
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && !exp)
			*off = *wr->end_dt--;
		else if (mp.zero != 0)
			ft_dbl_sgnvld(wr, off, wr->end, '0');
		else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
			*off = '0';
		else if (mp.pnum > wr->sz)
			ft_dbl_sgnvld(wr, off, wr->off - mp.pnum, 'k');
		else
			ft_dbl_sgnvld(wr, off, wr->off - wr->sz, 'k');
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
	unsigned int	(*ft_mdbl)(t_wrtr *);
	void	(*ft_dbl)(t_wrtr *, char *);

	num = dbl;
	wr.sz = ft_numlen(&num, '-');
	wr.nd = nd;
	wr.d = &dbl;
	if (dbl < 0)
		nd->map.sgned = 1;
	ft_mdbl = ft_mng_dbl;
	ft_dbl = ft_wr_dbl;
	if (ft_mem_mng(&wr, ft_mdbl) == 0)
		return (0);
	wr.dt = ft_mkdbl(dbl, wr.sz);
	if (wr.dt == NULL)
		return (0);
	ft_wr_mch(&wr, ft_dbl);
	printf("D:\t Debuggin dbl: %s\n", nd->lf.off);
	free(wr.dt);
	return (1);
}
/*----------------------START chr CONVERSION-------------------*/
static u_int	ft_mng_chr(t_wrtr *wr)
{
	t_map	mp;

	mp = wr->nd->map;
	if (mp.fnum > wr->sz)
		return (mp.fnum);
	else
		return (wr->sz);
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
	unsigned int	(*ft_mchr)(t_wrtr *);
	void	(*ft_chr)(t_wrtr *, char *);
	t_wrtr	wr;

	ft_chr = ft_wr_chr;
	ft_mchr = ft_mng_chr;
	wr.sz = 1;
	wr.nd = nd;
	wr.dt = ft_mkchr(chr);
	wr.d = &chr;
	if (wr.dt == NULL)
		return (0);
	if (ft_mem_mng(&wr, ft_mchr) == 0)
		return (0);
	ft_wr_mch(&wr, ft_chr);
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
/*Parcheado, corregido para contemplar el espacio requerido cuando hex == 0*/
static u_int	ft_mng_hex(t_wrtr *wr)
{
	int		hashed;
	t_map	mp;

	hashed = 0;
	mp = wr->nd->map;
	if (mp.hash != 0)
		hashed = 2;
	if (*(u_int *) wr->d == 0 && mp.fnum >= 1 && mp.fnum >= mp.pnum)
		return (mp.fnum);
	else if (*(u_int *) wr->d == 0 && mp.pnum >= 1 && mp.pnum >= mp.fnum)
		return (mp.pnum);
	else if (*(u_int *) wr->d == 0 && mp.fnum < 1 && mp.pnum < 1)
		return (0);
	else if (mp.fnum > mp.pnum + hashed)
	{
		if (mp.fnum <= wr->sz + hashed)
			return (wr->sz + hashed);
		else
			return (mp.fnum);
	}
	else if (mp.pnum > wr->sz)
		return (mp.pnum + hashed);
	else
		return (wr->sz + hashed);
}
/*Parcheado, corrigiendo error a la hora de eliminar memoria.*/
static char	*ft_mem_asgn(char **tmp, char **dt, u_int num, u_int *counter)
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
/*Parcheado, era redudante y no contemplaba el caso de hex == 0*/
static char	*ft_mkhex(unsigned int hex, t_caphex capital)
{
	u_int	num;
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
/*Parcheado, no muchas pruebas.*/
static void ft_hex_vldtn(char *off, t_wrtr *wr, int f, t_caphex capital)
{
	t_map	mp;
	int		exp;

	mp = wr->nd->map;
	exp = (*(u_int *) wr->d == 0);
	if (mp.hash != 0 && off == wr->off && !exp)
		*off = '0';
	else if (mp.hash != 0 && off == wr->off + 1 && !exp)
		*off = 23 + capital;
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum - wr->sz + f)
		*off = '0';
	else if (mp.pnum > wr->sz && off < wr->off + mp.pnum + f && !exp)
		*off = *wr->off_dt++;
	else if (mp.pnum <= wr->sz && off < wr->off + wr->sz + f && !exp)
		*off = *wr->off_dt++;
	else
		*off = 'k';
}
/*Parcheado, no muchas pruebas.*/
static void	ft_hash_vldtn(t_map mp, char *off, t_wrtr *wr, t_caphex cp)
{
	int	exp;

	exp = (mp.hash != 0 && *(u_int *) wr->d != 0);
	if (mp.zero != 0 && exp && off > wr->end + 1)
		*off = '0';
	else if (mp.zero != 0 && exp && off == wr->end + 1)
		*off = 23 + cp;
	else if (mp.zero != 0 && exp && off == wr->end)
		*off = '0';
	else if (mp.zero != 0 && (mp.hash == 0 || *(u_int *) wr->d == 0))
		*off = '0';
	else if (mp.pnum > wr->sz && off >= wr->off - mp.pnum + 1)
		*off = '0';
	else if (mp.pnum > wr->sz && exp && off == wr->off - mp.pnum)
		*off = 23 + cp;
	else if (mp.pnum > wr->sz && exp && off == wr->off - mp.pnum - 1)
		*off = '0';
	else if (mp.pnum <= wr->sz && exp && off == wr->off - wr->sz)
		*off = 23 + cp;
	else if (mp.pnum <= wr->sz && exp && off == wr->off - wr->sz - 1)
		*off = '0';
	else
		*off = 'k';
}

static void	ft_wr_hex(t_wrtr *wr, char *off)
{
	t_map	mp;
	
	mp = wr->nd->map;
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && *(u_int *) wr->d != 0)
			*off = *wr->end_dt--;
		else
			ft_hash_vldtn(mp, off, wr, LOWER);

	}
	else
	{
		if (mp.hash != 0 && *(u_int *) wr->d != 0)
			ft_hex_vldtn(off, wr, 2, LOWER);
		else
			ft_hex_vldtn(off, wr, 0, LOWER);
	}
}

int ft_hex_exp(t_nd *nd, unsigned int hex)
{
	t_wrtr			wr;
	unsigned int	(*ft_mhex)(t_wrtr *);
	void			(*ft_hex)(t_wrtr *, char *);

	ft_mhex = ft_mng_hex;
	ft_hex = ft_wr_hex;
	wr.nd = nd;
	wr.dt = ft_mkhex(hex, LOWER);
	wr.d = &hex;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mhex) == 0)
		return (0);
	ft_wr_mch(&wr, ft_hex);
	printf("D:\t Debuggin hex: %s\t%d\t%s\n", nd->lf.off, hex, wr.dt);
	return (1);
}
/*----------------------START usgn CONVERSION---------------------*/
int ft_usgn_exp(t_nd *nd, unsigned int usgn)
{
	
	printf("D:\t Debuggin usgn: %d\t%d\n",nd->is_lf, usgn);
	return (0);
}
/*----------------------START chex CONVERSION--------------------*/
static void	ft_wr_chex(t_wrtr *wr, char *off)
{
	t_map	mp;
	
	mp = wr->nd->map;
	if (wr->rg_lf == 1)
	{
		if (off >= wr->off - wr->sz + 1 && *(u_int *) wr->d != 0)
			*off = *wr->end_dt--;
		else
			ft_hash_vldtn(mp, off, wr, UPPER);

	}
	else
	{
		if (mp.hash != 0 && *(u_int *) wr->d != 0)
			ft_hex_vldtn(off, wr, 2, UPPER);
		else
			ft_hex_vldtn(off, wr, 0, UPPER);
	}
}

int ft_chex_exp(t_nd *nd, unsigned int hx)
{
	t_wrtr			wr;
	unsigned int	(*ft_mchex)(t_wrtr *);
	void			(*ft_chex)(t_wrtr *, char *);

	ft_mchex = ft_mng_hex;
	ft_chex = ft_wr_chex;
	wr.nd = nd;
	wr.dt = ft_mkhex(hx, UPPER);
	wr.d = &hx;
	if (wr.dt == NULL)
		return (0);
	wr.sz = ft_strlen(wr.dt);
	if (ft_mem_mng(&wr, ft_mchex) == 0)
		return (0);
	ft_wr_mch(&wr, ft_chex);
	printf("D:\t Debuggin hex: %s\t%d\t%s\n", nd->lf.off, hx, wr.dt);
	return (1);
}
/*------------------START ptr CONVERSION-----------------------*/
int ft_ptr_exp(t_nd *nd, void * ptr)
{
	printf("D:\t Debuggin ptr: %d\t%p\n", nd->is_lf, ptr);
	return (0);
}
/*------------------START per CONVERSION-----------------------*/
int	ft_per_exp(t_nd *nd)
{
	printf("D:\t Debuggin per %p\n", nd);
	return (0);
}