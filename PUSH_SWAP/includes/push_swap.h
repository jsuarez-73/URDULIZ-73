/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:18:22 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/29 09:58:14 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

typedef struct s_push
{
	int		*s_a;
	int		*s_b;
	t_uns	n;
	t_uns	n_a;
	t_uns	id_a;
	t_uns	n_b;
	t_uns	id_b;
	t_uns	mov_n;
	t_uns	pshb;
}	t_push;

enum e_psh
{
	NN = 0x7FFFFFFF,
	STACK_A = 0,
	STACK_B = 1,
	QUIET = 0,
	NO_QUIET =1
} ;

typedef struct s_idtm
{
	t_uns	id_a;
	t_uns	id_b;
	int		m_cst;
}	t_idtm;

int		ft_swap_a(t_push *p);
int		ft_push_a(t_push *p);
int		ft_rot_a(t_push *p, int vrbose);
int		ft_revrot_a(t_push *p, int vrbose);
int		ft_swap_b(t_push *p);
int		ft_push_b(t_push *p);
int		ft_rot_b(t_push *p, int vrbose);
int		ft_revrot_b(t_push *p, int vrbose);
int		ft_2swap(t_push *p);
int		ft_2rot(t_push *p, int vrbose);
int		ft_2revrot(t_push *p, int vrbose);
void	ft_clean_push(t_push *p);
void	ft_think(t_push *p);
int		ft_is_ordered(t_push *p);
void	ft_show_stacks(t_push *p);
int		ft_min_rot(t_push *p, t_uns nmv, int (*f)(t_push *, int), int vrbose);

#endif