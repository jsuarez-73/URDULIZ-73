/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:38:24 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/20 20:47:11 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	else if (!*lst)
		return ;
	else
	{
		while ((*lst))
		{
			del((*lst)->content);
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp);
		}
	}
}
