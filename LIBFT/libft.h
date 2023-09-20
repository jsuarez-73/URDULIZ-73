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
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// # define INT_MAX	2147483647
// # define INT_MIN	-2147483648
// # define CHAR_BIT	8
// # define SCHAR_MIN	-128
// # define SCHAR_MAX	127
// # define UCHAR_MAX	255
// # define CHAR_MIN	-128
// # define CHAR_MAX	127
// # define MB_LEN_MAX	16
// # define SHRT_MIN	-32768
// # define SHRT_MAX	32767
// # define USHRT_MAX	65535
// # define UINT_MAX	4294967295
// # define LONG_MIN	-9223372036854775808
// # define LONG_MAX	9223372036854775807
// # define ULONG_MAX	18446744073709551615

typedef long unsigned int	t_size;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_bzero(void *w, t_size q);
int		ft_isalnum(int n);
int		ft_isalpha(int n);
int		ft_isascii(int n);
int		ft_isdigit(int n);
int		ft_isprint(int n);
void	*ft_memcpy(void *dest, const void *src, t_size n);
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
void	*ft_calloc(t_size nmemb, t_size size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, t_size len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//Bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

#endif