/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flusher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:16:43 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/12/01 15:35:06 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_gdata *gdt, int status, int parent)
{
	if (parent)
		ft_flush_semaphores(gdt, CLS_UNLINK, FLUSH_ALL);
	else
		ft_flush_semaphores(gdt, CLOSE, FLUSH_ALL);
	if (gdt->id)
		free(gdt->id);
	exit(status);
}
