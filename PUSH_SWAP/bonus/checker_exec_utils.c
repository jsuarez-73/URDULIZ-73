/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:30:29 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 08:30:52 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_push_lst(t_list *lst, char *buf, int l_rd, t_push *p)
{
	t_list	*nd;

	if (lst->content == NULL)
		lst->content = ft_assign_mov(buf, l_rd);
	else
	{
		nd = (t_list *)malloc(sizeof(t_list));
		if (!nd)
		{
			ft_clean_mng(lst, p);
			exit(-1);
		}
		nd->content = ft_assign_mov(buf, l_rd);
		nd->next = NULL;
		ft_lstadd_back(&lst, nd);
	}
}

void	ft_clean_mng(t_list *lst, t_push *p)
{
	t_list	*tmp;

	lst = lst->next;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	ft_clean_push(p);
}

void	ft_exec_lst(t_list *lst, t_push *p)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp->content)
	{
		if (!tmp->next && tmp->content)
		{
			((int (*)(t_push *, int))tmp->content)(p, QUIET);
			tmp = tmp->next;
		}
		while (tmp)
		{
			((int (*)(t_push *, int))tmp->content)(p, QUIET);
			tmp = tmp->next;
		}
	}
	if (ft_is_ordered(p) && p->n_b == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_clean_mng(lst, p);
}
