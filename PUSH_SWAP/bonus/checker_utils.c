/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:24:52 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 00:12:23 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
/*MOdificar esta fucnion para que envie la limpieza a clean_lst*/
short	ft_check_in(char *b, int l, t_push *p, t_list *lst)
{
	int (*cmp)(const char *, const char *, t_size);

	cmp = ft_strncmp;
	if (l == 4 && cmp(b, "rra", 3) == 0)
		return (1);
	else if (l == 4 && cmp(b, "rrb", 3) == 0)
		return (1);
	else if (l == 4 && cmp(b, "rrr", 3) == 0)
		return (1);
	else if (l == 3 && (cmp(b, "sa", 2) == 0 || cmp(b, "sb", 2) == 0))
		return (1);
	else if (l == 3 && (cmp(b, "ss", 2) == 0 || cmp(b, "ra", 2) == 0))
		return (1);
	else if (l == 3 && (cmp(b, "rb", 2) == 0 || cmp(b, "rr", 2) == 0))
		return (1);
	else if (l == 3 && (cmp(b, "pb", 2) == 0 || cmp(b, "pa", 2) == 0))
		return (1);
	else if (l == 0)
		return (1);
	else
	{
		write(STD_ERR, "Error\n", 6);
		ft_clean_lst(lst);
		if (b)
			free(b);
		ft_clean_push(p);
		exit(-1);
	}
	return (0);
}

void	*ft_assign_mov(char *b, int l)
{
	if (l == 4 && ft_strncmp(b, "rra", 3) == 0)
		return ((void *)ft_revrot_a);
	else if (l == 4 && ft_strncmp(b, "rrb", 3) == 0)
		return ((void *)ft_revrot_b);
	else if (l == 4 && ft_strncmp(b, "rrr", 3) == 0)
		return ((void *)ft_2revrot);
	else if (l == 3 && ft_strncmp(b, "sa", 2) == 0)
		return ((void *)ft_swap_a);
	else if (l == 3 && ft_strncmp(b, "sb", 2) == 0)
		return ((void *)ft_swap_b);
	else if (l == 3 && ft_strncmp(b, "ss", 2) == 0)
		return ((void *)ft_2swap);
	else if (l == 3 && ft_strncmp(b, "ra", 2) == 0)
		return ((void *)ft_rot_a);
	else if (l == 3 && ft_strncmp(b, "rb", 2) == 0)
		return ((void *)ft_rot_b);
	else if (l == 3 && ft_strncmp(b, "rr", 2) == 0)
		return ((void *)ft_2rot);
	else if (l == 3 && ft_strncmp(b, "pa", 2) == 0)
		return ((void *)ft_push_a);
	else if (ft_strncmp(b, "pb", 2) == 0)
		return ((void *)ft_push_b);
	return (NULL);
}

void	ft_push_lst(t_list *lst, char *buf, int l_rd)
{
	t_list	*nd;

	if (lst->content == NULL)
		lst->content = ft_assign_mov(buf, l_rd);
	else
	{
		nd = (t_list *)malloc(sizeof(t_list));
		if (!nd)
		{
			ft_clean_lst(lst);
			exit(-1);
		}
		nd->content = ft_assign_mov(buf, l_rd);
		nd->next = NULL;
		ft_lstadd_back(&lst, nd);
	}
}
/*Cambiar esta funcion par alimpiar toda la memoria.*/
void	ft_clean_lst(t_list *lst)
{
	t_list	*tmp;

	lst = lst->next;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
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
	ft_clean_lst(lst);
	if (ft_is_ordered(p) && p->n_b == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_clean_push(p);
}
