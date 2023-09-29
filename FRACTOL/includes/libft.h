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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stddef.h>
# include <stdlib.h>
	// void *malloc(size_t size)
	// void free(void *ptr)
	// [[noreturn]] void exit(int status);
	/*The exit(int status) function causes normal process termination and the
       least significant byte of status (i.e., status & 0xFF) is
       returned to the parent (see wait(2)).*/
# include <unistd.h>
	// int close(int fd), 
	// ssize_t read(int fd, void buf[.count], size_t count),
	// ssize_t write(int fd, const void buf[.count], size_t count).
# include <stdarg.h>
	// void va_start(va_list ap, argN);
	// void va_copy(va_list dest, va_list src);
	// type va_arg(va_list ap, type);
	// void va_end(va_list ap);

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

//GNL
typedef enum e_watch
{
	LOCK = 1,
	UNLOCK = 0,
	RETURN = 2
}	t_watch;

typedef struct s_gnl
{
	int				fd;
	char			*e_bf;
	char			*s_buf;
	char			buf[BUFFER_SIZE];
	int				b_rd;
	char			*linea;
	unsigned int	b_ln;
	t_watch			watcher;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
t_gnl	*ft_search_add(t_gnl *gnl, int fd, t_gnl **gl);
int		ft_guard(char **ln, t_gnl **gl, t_gnl *ls, int fd);
int		ft_mem_mng(char **ln, t_gnl **gl, unsigned int *b_ln);

//PRINTF

typedef unsigned int	t_uns;

typedef enum e_caphex
{
	UPPER = 65,
	LOWER = 97
}	t_caphex;

typedef enum e_ndtype
{
	FLAGS,
	FIELD,
	PRCSN
}	t_ndtype;

typedef struct s_map
{
	unsigned int	plus;
	unsigned int	hash;
	unsigned int	minus;
	unsigned int	zero;
	unsigned int	space;
	unsigned int	fnum;
	unsigned int	fstar;
	unsigned int	pnum;
	unsigned int	pstar;
	unsigned int	ppoint;
	unsigned int	sgned;
}	t_map;

typedef struct t_elem
{
	char	*off;
	char	*end;
}	t_lm;

typedef struct s_nd
{
	t_lm	lf;
	t_lm	prcsn;
	t_lm	flgs;
	t_lm	wdth;
	t_map	map;
	short	is_lf;
}	t_nd;

typedef struct s_wrtr
{
	t_nd	*nd;
	char	*dt;
	t_uns	sz;
	char	*off;
	char	*end;
	int		rg_lf;
	char	*off_dt;
	char	*end_dt;
	void	*d;
}	t_wrtr;

typedef struct s_fstr
{
	t_nd			nd;
	t_lm			lm;
	unsigned int	q_nd;
	struct s_fstr	*nxt;
}	t_fstr;

/*Worker functions*/
int				ft_printf(const char *fstr, ...);
int				ft_tree_drv(char *fstr, t_fstr *root);
void			ft_nd_drv(t_fstr *root);
int				ft_parser(t_fstr *root);
void			ft_get_maps(t_map *map, char *off, char *end, t_ndtype type);
void			ft_init_map(t_map *map);
int				ft_exp_arg(va_list list, t_fstr *root);
int				ft_outmch(t_fstr *root);
int				ft_freemch(t_fstr *root);
char			*ft_matcher(char *str, char *set);

/*Expander functions*/
int				ft_dbl_exp(t_nd *nd, int dbl);
int				ft_str_exp(t_nd *nd, char *str);
int				ft_chr_exp(t_nd *nd, unsigned char chr);
int				ft_hex_exp(t_nd *nd, unsigned int hex);
int				ft_usgn_exp(t_nd *nd, unsigned int usgn);;
int				ft_chex_exp(t_nd *nd, unsigned int hx);
int				ft_ptr_exp(t_nd *nd, void *ptr);
int				ft_per_exp(t_nd *nd);
void			ft_init_wr(t_wrtr *wr);

/*Utils functions*/
int				ft_mem_mng_p(t_wrtr *wr, t_uns (*m)(t_wrtr *));
char			*ft_mem_asgn(char **tmp, char **dt, long num, t_uns *counter);
unsigned int	ft_strlen_p(char *str);
char			*ft_mkhex(unsigned long hex, t_caphex capital);
void			ft_hash_vldtn(t_map mp, char *off, t_wrtr *wr, t_caphex cp);
void			ft_hex_vldtn(char *off, t_wrtr *wr, int f, t_caphex capital);
t_uns			ft_mng_hex(t_wrtr *wr);
char			*ft_mkdbl(t_uns n);

/*Writer Machine functions*/
void			ft_wr_mch(t_wrtr *wr, void (*f)(t_wrtr *, char *));
void			ft_rg_lf(t_wrtr *wr, void (*f)(t_wrtr *, char *));
void			ft_lf_rg(t_wrtr *wr, void (*f)(t_wrtr *, char *));

#endif