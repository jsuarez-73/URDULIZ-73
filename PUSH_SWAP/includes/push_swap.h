/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:18:22 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/17 10:13:17 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

typedef struct s_push
{
	int		*stack_a;
	int		*stack_b;
	t_uns	elem;
	t_uns	elem_a;
	//Establecer una variable por cada movimiento
	//Para asignarle 1 en cada bit cuando se utilice.

}	t_push;

#endif