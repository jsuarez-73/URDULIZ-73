/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:54:09 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/02 17:13:02 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "limits.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# define DEF_WIDTH 900
# define DEF_HEIGHT 900
# ifdef MAC

typedef enum e_kmap
{
	ESC = 53,
	ARR_UP = 126,
	ARR_DW = 125,
	ARR_LF = 123,
	ARR_RG = 124,
	CLICK_LF = 1,
	CLICK_RG = 2,
	CLICK_MD = 3,
	SCROLL_UP = 5,
	SCROLL_DW = 4
}	t_kmap;

# endif
# ifdef LINUX

typedef enum  e_kmap
{
	ESC = 65307,
	ARR_UP = 65362,
	ARR_DW = 65364,
	ARR_LF = 65361,
	ARR_RG = 65363,
	CLICK_LF = 1,
	CLICK_RG = 2,
	CLICK_MD = 3,
	SCROLL_UP = 4,
	SCROLL_DW = 5
}	t_kmap;

# endif

typedef struct s_srv
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*off;
	int		bpp;
	int		ln_len;
	int		endian;
	int		iter;
	int		*colors;
	int		w;
	int		h;
	double	my;
	double	mx;
	int		crange;
	double	cx;
	double	cy;
	char	chosen;
	double	tx;
	double	ty;
	char	arg_msk;

}	t_xsrv;

typedef enum e_ev
{
	KDOWN = 2,
	KUP = 3,
	BDOWN = 4,
	BUP = 5,
	MOTION = 6,
	EXPOSE = 12,
	DESTROY = 17
}	t_ev;

typedef enum e_msk
{
	DEF_MSK = 0L,
	KD_MSK = (1L << 0),
	KU_MSK = (1L << 1),
	BD_MSK = (1L << 2),
	BU_MSK = (1L << 3),
	MOT_MSK = (1L << 6),
	BT1_MSK = (1L << 8),
	BT4_MSK = (1L << 11),
	BT5_MSK = (1L << 12),
	EXP_MSK = (1L << 15)
}	t_msk;

int		ft_get_color_scheme(t_xsrv *sf);
void	ft_hook_init(t_xsrv *sf);
void	ft_render(t_xsrv *sf);
int		ft_init(t_xsrv *sf);
int		ft_mondelbrot(t_xsrv *sf, double xp, double yp);
int		ft_julia(t_xsrv *sf, double xp, double yp);
void	ft_attr_mngr(t_xsrv *sf, int argc, char **argv);
int		ft_cubic(t_xsrv *sf, double xp, double yp);

//Utils
double	ft_atof(char *s);
int		ft_help_msg(void);

#endif