/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42Urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:22:00 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/05/11 21:22:00 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

typedef unsigned int	t_size;

void	ft_bzero(void *w, t_size q);
int		ft_isalnum(int n);
int		ft_isalpha(int n);
int		ft_isascii(int n);
int		ft_isdigit(int n);
int		ft_isprint(int n);
void	*ft_memcpy(void *restrict dest, const void *restrict src, t_size n);
void	*ft_memset(void *s, int c, t_size n);
t_size	ft_strlen(const char *c);
int		ft_memcmp(const void *s1, const void *s2, t_size n);
void	*ft_memmove(void *dest, const void *src, unsigned int n);
void	*ft_memchr(const void *s, int c, t_size n);
int		ft_atoi(const char *s1);
char	*ft_strchr(const char *s, int c);
t_size	ft_strlcat(char *dest, const char *src, t_size n);
t_size	ft_strlcpy(char *dest, const char *src, t_size n);
int		ft_strncmp(const char *s1, const char *s2, t_size n);
char	*ft_strnstr(const char *s1, const char *s2, t_size n);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
#endif