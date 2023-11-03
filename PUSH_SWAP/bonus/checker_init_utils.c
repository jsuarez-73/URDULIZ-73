/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:24:52 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/11/03 09:51:01 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	ft_check_out(char *b, t_list *lst, t_push *p)
{
	write(STD_ERR, "Error\n", 6);
	if (b)
		free(b);
	ft_clean_mng(lst, p);
	exit(-1);
}

short	ft_check_in(char *b, int l, t_push *p, t_list *lst)
{
	int	(*cmp)(const char *, const char *, t_size);

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
		ft_check_out(b, lst, p);
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
