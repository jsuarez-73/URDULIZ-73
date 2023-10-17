/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacka_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:46:31 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/17 10:20:48 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap_a(t_push *push)
{
	int		tmp;
	t_uns	index;

	index = push->elem - push->elem_a;
	if (index < push->elem - 1)
	{
		tmp = *(push->stack_a + index);
		*(push->stack_a + index) = *(push->stack_a + index + 1);
		*(push->stack_a + index + 1) = tmp;
		return (1);
	}
	else
		return (0);
}

void	ft_push_a(t_push *push)
{
	int		tmp;
	t_uns	index;

	index = push->elem_a;
	if (index < push->elem)
	{
		tmp = *push->stack_a;
		*push->stack_a = *push->stack_b;
		*push->stack_b = tmp;
	}
}