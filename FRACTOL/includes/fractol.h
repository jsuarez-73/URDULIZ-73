/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:54:09 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/29 19:23:04 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include <fcntl.h>
	//int open(const char *pathname, int flags, mode_t mode)
# include <stdio.h>
	// void perror(const char *s)
	/*The perror() function produces a message on standard error
	   describing the last error encountered during a call to a system
	   or library function.

	   First (if s is not NULL and *s is not a null byte ('\0')), the
	   argument string s is printed, followed by a colon and a blank.
	   Then an error message corresponding to the current value of errno
	   and a new-line.

	   To be of most use, the argument string should include the name of
	   the function that incurred the error.*/
# include <string.h>
	// char *strerror(int errnum)
	/*The strerror() function returns a pointer to a string that
	   describes the error code passed in the argument errnum, possibly
	   using the LC_MESSAGES part of the current locale to select the
	   appropriate language.  (For example, if errnum is EINVAL, the
	   returned description will be "Invalid argument".)  This string
	   must not be modified by the application, but may be modified by a
	   subsequent call to strerror() or strerror_l().  No other library
	   function, including perror(3), will modify this string.*/
# include <math.h>
# include "mlx.h"
# define	DEF_WIDTH 900
# define	DEF_HEIGHT 900
typedef struct s_srv
	{
		void	*mlx; //Puntero a servidor.
		void	*win; //Puntero a ventana.
		void	*img; //puntero a la imagen creada
		char	*off; //Offset en memoria en donde empieza la imagen
		int		bpp; // bits requeridos para representar un pixel
		int		ln_len; //longitud de la linea de una imagen
		int		endian; //big-endian o little-endian
		t_uns	iter;//Almacena la cantidad de iteraciones que se desean
		int		*colors;//ALmacena la paleta de colores a utilziar.
		int		w;//Ancho inicial de la imagen
		int		h;//Altura inicial de la imagen.
		double	my;//Valor maximo del plano complejo en Y
		double	mx;//Valor maximo del plano complejo en X
		int		crange;//Range del color scheme
		double	cx;//Choose Julia Set from complex number x
		double	cy;//Choose Julia Set from complex number y
		char	chosen;//Inicial del fractal elegido
		double	tx;//Traslacion en X
		double	ty;//Traslacion en Y
		char	arg_msk;//Before initialization to set arguments CLI;

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
}      t_ev;

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

// typedef enum e_color
// {
// 	RED = 0xC0392B,
// 	RED_L = 0xE74C3C,
// 	PURPLE = 0x7D3C98,
// 	PURPLE_L = 0x9B59B6,
// 	BLUE = 0x2980B9,
// 	BLUE_L = 0x3498DB,
// 	GREEN_DL = 0x1ABC9C,
// 	GREEN_UL = 0x16A085,
// 	GREEN = 0X27AE60,
// 	GREEN_L = 0x2ECC71,
// 	YELLOW = 0xF1C40F,
// 	YELLOW_L = 0xF39C12,
// 	ORANGE_L = 0xE67E22,
// 	ORANGE = 0xD35400,
// 	WHITE = 0xECF0F1,
// 	GREY = 0x7F8C8D,
// 	BLACK = 0x17202A
// }	t_color;
void	ft_get_color_scheme(t_xsrv *sf);
void	ft_hook_init(t_xsrv *sf);
void	ft_render(t_xsrv *sf);
void	ft_init(t_xsrv *sf);
int		ft_mondelbrot(t_xsrv *sf, double xp, double yp);
int		ft_julia(t_xsrv *sf, double xp, double yp);
void	ft_attr_mngr(t_xsrv *sf, int argc, char **argv);
int		ft_cubic(t_xsrv *sf, double xp, double yp);

#endif