/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:10:00 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/02 23:32:35 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "push_swap.h"

short	ft_check_in(char *b, int l, t_push *, t_list *);
void	*ft_assign_mov(char *b, int l);
void	ft_push_lst(t_list *lst, char *buf, int l_rd);
void	ft_clean_lst(t_list *lst);
void	ft_exec_lst(t_list *lst, t_push *p);

#endif