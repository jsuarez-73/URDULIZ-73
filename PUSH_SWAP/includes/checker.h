/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:10:00 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 07:51:30 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include "push_swap.h"

short	ft_check_in(char *b, int l, t_push *, t_list *);
void	*ft_assign_mov(char *b, int l);
void	ft_push_lst(t_list *lst, char *buf, int l_rd, t_push *);
void	ft_clean_mng(t_list *lst, t_push *p);
void	ft_exec_lst(t_list *lst, t_push *p);

#endif