/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:03:34 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/16 18:12:13 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;

	new = (char *)malloc(ft_strlen(s) + 1);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s, ft_strlen(s) + 1);
	return (new);
}
