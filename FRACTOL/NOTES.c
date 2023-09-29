/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTES.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:15:58 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/22 21:05:07 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

MinilibX

Images:

		void *	mlx_new_image ( void *mlx_ptr, int width, int height );

		char *	mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );

		int	mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );

		unsigned int	mlx_get_color_value ( void *mlx_ptr, int color );

		void *	mlx_xpm_to_image ( void *mlx_ptr, char **xpm_data, int *width, int *height );

		void *	mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );

		int	mlx_destroy_image ( void *mlx_ptr, void *img_ptr );

	mlx_new_image(): Crea una imagen en memoria, retorna un identificador para manipular la imagen.
		Sus argumentos son, el tamano de la imagen, y la coneccion al servidor X.

	mlx_put_image_to_window(): Se utiliza para colocar la imagen en la ventana correspondiente, esto
		luego de haber realizado el dibujado correspondiente sobre la misma.
		Los argumentos requeridos son: coneccion al servidor X, la ventana donde se colocara la imagen,
		la imagen a colocarse (img_ptr) y (x, y) representan la coordenada en donde se colocara la imagen.

	mlx_get_data_addr(): Retorna informacion acerca de la imagen que fue creada con mlx_new_image(),
		- img_ptr: representa la imagen de la cual se desea obtener la informacion para ser modificada y
			dibujada.
		- bits_per_pixel: este parametro lo utiliza la funcion para establecer la cantidad de bits que 
			se necesitan para colorear un pixel, esto se conoce como profundidad de la imagen.
			**Dependiendo de la pantalla el numero de bits_per_pixel puede cambiar.
		- size_line: este parametro es usado por la funcion para establecer la cantidad de bytes usados
			para almacenar una linea de la imagen en memoria. Necesario para mover de una linea a otra
			en la imagen.
		- endian: indica si el color del pixel en la imagen necesita ser guardado como little-endian (0)
			o big-endian (1). EJemplo: 0x4A3B2C1D Es big-endian, sigue el orden natural en que se codifica
			la memoria, es decir, la secuencia en que se codifica en memoria es: {4A, 3B, 2C, 1D}, 
			mientras que 0x4A3B2C1D sigue el paralelismo "no es como las cosas empiezan, sino como terminan"
			con lo cual big-endian se codifica en memoria siguiendo la siguiente secuencia {1D, 2C, 3B, 4A}.
		
		Retorna un char * que representa el inicio del area de memoria donde la imagen esta almacenada.
		Desde esta direccion de memoria el primer grupo de bits (bits_per_pixel) representa el primer pixel
		de la primera linea de la imagen, el segundo grupo de bits (bits_per_pixel) representa el segundo
		pixel de la imagen, y asi sucesivamente.

	mlx_destroy_image(): Destruya la imagen dada.

	mlx_get_color_value(): Se encarga de traducir el parametro color y retornar un unsigned int de tal
		modo que X-Server sea capaz de entender sin importar el numero de bits_per_pixel que necesite
		la pantalla, debido a que los bits menos significativos de este unsigned int son los tomados
		como el color para ser guardados en la imagen. (Iportante si el computador es little o big endian)

	mlx_xpm_to_image(): Utiliza xpm data para llenar una imagen.

	mlx_xpm_file_to_image(): Utiliza un file para llenar una imagen.

Pixel_put:

		int	mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );

		int	mlx_string_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string );
	
	mlx_pixel_put(): Se encarga de dibujar en la ventana especificada siguiendo la posicion dada por las
		coordenadas (x,y) y el color asignado.
	
	mlx_string_put(): Se encarga de colocar el string en la posicion indicada por las coordenadas (x,y)

	┌────────────────────────────────────────────────┐
	│                 Color Integer                  │
	├───────────────┬────────┬────────┬───────┬──────┤
	│Interpretation │   α    │   R    │   G   │  B   │	---> 0XFF00FF00 cada dupla hexadecimal
	├───────────────┼────────┼────────┼───────┼──────┤					representa un byte.
	│   Bit numbers │ 31..24 │ 23..16 │ 15..8 │ 7..0 │
	└───────────────┴────────┴────────┴───────┴──────┘

Manejando Ventanas:

		void *	mlx_new_window ( void *mlx_ptr, int size_x, int size_y, char *title );

		int	mlx_clear_window ( void *mlx_ptr, void *win_ptr );

		int	mlx_destroy_window ( void *mlx_ptr, void *win_ptr );
	
	mlx_new_window(): Se encarga de crear una nueva ventana en pantalla, siguiendo las especificaciones
		indicadas por los parametros size x, size y, la coneccion al X-server y el titulo en la barra.
	
	mlx_clear_window(): Borra en negro la ventana, (pinta toda la ventana de negro).

	mlx_destroy_window(): Destruye la ventana de la memoria.

	**Si falla retorna NULL.

Servidor X:

		void *	mlx_init ();

	mlx_init(): Se encarga de iniciar el X-Servidor, recibe y envia request y response de lo que ocurre
		en el sistema grafico, con lo cual es necesario establecer una coneccion entre el cliente
		(nuestro software) y el servidor (X-server).
		Por una parte recibe request de lo que se quiere dibujar en la interfaz y por otro envia responses
		de los eventos que ocurren con el mouse y el teclado.

Manejando Eventos:

		int	mlx_loop ( void *mlx_ptr );

		int	mlx_key_hook ( void *win_ptr, int (*funct_ptr)(), void *param );

		int	mlx_mouse_hook ( void *win_ptr, int (*funct_ptr)(), void *param );

		int	mlx_expose_hook ( void *win_ptr, int (*funct_ptr)(), void *param );

		int	mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );

		void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	
	mlx_loop(): La funcion nunca retorna, y se encarga de esperar eventos desde el servidor para luego
		llamar una funcion asociada a dicho evento, solo se requiere del identificador de la coneccion
		al servidor.

		**Cada ventana puede definir una funcion diferente para cada evento

	[mlx_key_hook() | mlx_mouse_hook() | mlx_expose_hook()]: Funcionan exactamente igual, la funcion invocada
		corresponde al tipo de evento ejecutado, cada una recibe como parametro un puntero a una funcion
		a la cual se pasa una direccion de memoria *param cada vez que el evento ocurre.
	
	mlx_loop_hook(): Es identica a los hook anteriores pero la funcion es llamada cuando ningun evento ocurre.
	(IDLE)

	*param: Es la direccion de memoria asociada cuando un evento de cualquier tipo ocurre, sin embargo, para
		eventos de mouse o de teclado, informacion adicional es pasada: keycode (correspondiente a la mascara
		para la tecla presionada) y (x,y) para indicar en donde fue clickeado el mouse en pantalla y button 
		indica cual boton fue presionado.
	
	mlx_hook(): Funcion con acceso generico a todos los eventos en X-Window, los eventos y las mask son tomados
		del archivo de cabecera X.h.
		**mlx_int_param_event.c Es el codigo fuente que indica como se llama a la funcion que pasamos para
		cada evento especifico.


CURIOSIDADES:

Los eventos y los mask deifinidos en la miniLibX juntos no realizan ninguna labor importante,
es decir, los mask es la manera que se tiene de crear a traves de 1L una lista que permita
activar o desactivar a nivel de bit los eventos que queremos que se nos sean notificados por
medio del X-Server, dicho de otra manera, los Mask Events no estan implementados. Al menos para
la version de Linux.

Por otra parte la libreria solo permite los eventos: Expose, MouseMotion, KeyPressed, KeyReleased,
ButtonPress, ButtonRelease, Generic (Este ultimo al parecer corresponde a enviar el evento creado
por X-Window a la funcion de manera general. Sin emabrgo parece no funcionar correctamente)

(1L << 12) Desplazamiento de 12 bits a la izquierda en 1 long type.




	


