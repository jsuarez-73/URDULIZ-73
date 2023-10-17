/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:16:58 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/09/16 18:51:33 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	t_size	s1_len;
	t_size	s2_len;
	char	*tmp;
	char	*end;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = (char *)malloc(s1_len + s2_len + 1);
	end = new + s1_len;
	tmp = new;
	if (new == NULL)
		return (NULL);
	while (tmp < end)
		*tmp++ = *s1++;
	while (end < new + s1_len + s2_len)
		*end++ = *s2++;
	*end = '\0';
	return (new);
}
