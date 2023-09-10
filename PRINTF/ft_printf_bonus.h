/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:56:29 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/10 18:38:20 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef unsigned int	t_uns;

typedef enum e_caphex
{
	UPPER = 65,
	LOWER = 97
}	t_caphex;

typedef enum e_ndtype
{
	FLAGS,
	FIELD,
	PRCSN
}	t_ndtype;

typedef struct s_map
{
	unsigned int	plus;
	unsigned int	hash;
	unsigned int	minus;
	unsigned int	zero;
	unsigned int	space;
	unsigned int	fnum;
	unsigned int	fstar;
	unsigned int	pnum;
	unsigned int	pstar;
	unsigned int	ppoint;
	unsigned int	sgned;
}	t_map;

typedef struct t_elem
{
	char	*off;
	char	*end;
}	t_lm;

typedef struct s_nd
{
	t_lm	lf;
	t_lm	prcsn;
	t_lm	flgs;
	t_lm	wdth;
	t_map	map;
	short	is_lf;
}	t_nd;

typedef struct s_wrtr
{
	t_nd	*nd;
	char	*dt;
	t_uns	sz;
	char	*off;
	char	*end;
	int		rg_lf;
	char	*off_dt;
	char	*end_dt;
	void	*d;
}	t_wrtr;

typedef struct s_fstr
{
	t_nd			nd;
	t_lm			lm;
	unsigned int	q_nd;
	struct s_fstr	*nxt;
}	t_fstr;

/*Worker functions*/
int				ft_printf(const char *fstr, ...);
int				ft_tree_drv(char *fstr, t_fstr *root);
void			ft_nd_drv(t_fstr *root);
int				ft_parser(t_fstr *root);
void			ft_get_maps(t_map *map, char *off, char *end, t_ndtype type);
void			ft_init_map(t_map *map);
int				ft_exp_arg(va_list list, t_fstr *root);
int				ft_outmch(t_fstr *root);
int				ft_freemch(t_fstr *root);
char			*ft_matcher(char *str, char *set);

/*Expander functions*/
int				ft_dbl_exp(t_nd *nd, int dbl);
int				ft_str_exp(t_nd *nd, char *str);
int				ft_chr_exp(t_nd *nd, unsigned char chr);
int				ft_hex_exp(t_nd *nd, unsigned int hex);
int				ft_usgn_exp(t_nd *nd, unsigned int usgn);;
int				ft_chex_exp(t_nd *nd, unsigned int hx);
int				ft_ptr_exp(t_nd *nd, void *ptr);
int				ft_per_exp(t_nd *nd);
void			ft_init_wr(t_wrtr *wr);

/*Utils functions*/
int				ft_mem_mng(t_wrtr *wr, t_uns (*m)(t_wrtr *));
char			*ft_mem_asgn(char **tmp, char **dt, long num, t_uns *counter);
unsigned int	ft_strlen(char *str);
char			*ft_mkhex(unsigned long hex, t_caphex capital);
void			ft_hash_vldtn(t_map mp, char *off, t_wrtr *wr, t_caphex cp);
void			ft_hex_vldtn(char *off, t_wrtr *wr, int f, t_caphex capital);
t_uns			ft_mng_hex(t_wrtr *wr);
char			*ft_mkdbl(u_int n);

/*Writer Machine functions*/
void			ft_wr_mch(t_wrtr *wr, void (*f)(t_wrtr *, char *));
void			ft_rg_lf(t_wrtr *wr, void (*f)(t_wrtr *, char *));
void			ft_lf_rg(t_wrtr *wr, void (*f)(t_wrtr *, char *));

#endif
