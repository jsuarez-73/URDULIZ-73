/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:17:15 by jsuarez-          #+#    #+#             */
/*   Updated: 2023/10/29 14:15:16 by jsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_show_stacks(t_push *p)
{
	t_uns	elem_n;
	t_uns	idx_a;
	t_uns	idx_b;
	t_uns	c;

	elem_n = p->n;
	idx_b = p->n_a;
	idx_a = p->n - p->n_a;
	c = 0;
	ft_printf("STACKS\nidx\tstack A\tstackB\n");
	while (elem_n--)
	{
		if (c >= idx_b && c >= idx_a)
			ft_printf("%u\t%d\t%d\n", c, *(p->s_a + c), *(p->s_b + c));
		else if (c >= idx_b && c < idx_a)
			ft_printf("%u\tX\t%d\n", c, *(p->s_b + c));
		else if (c < idx_b && c >= idx_a)
			ft_printf("%u\t%d\tX\n", c, *(p->s_a + c));
		else
			ft_printf("%u\tX\tX\n", c);
		c++;
	}
	ft_printf("\n");
}

int	ft_is_ordered(t_push *p)
{
	t_uns	c;

	c = p->n;
	while (c-- > (p->id_a + 1))
		if (*(p->s_a + c) < *(p->s_a + c - 1))
			return (0);
	return (1);
}

void	ft_init_push(int argc, char **argv, t_push *p)
{
	int	cntr;

	cntr = 0;
	p->n = --argc;
	p->n_a = p->n;
	p->id_a = 0;
	p->id_b = p->n;
	p->n_b = 0;
	p->mov_n = 0;
	p->pshb = 1;
	while (argc--)
	{
		*(p->s_b + cntr) = NN;
		*(p->s_a + cntr++) = ft_atoi(*(++argv));
	}
}

void	ft_check_args(int argc, char **argv, t_push *p)
{
	if (argc > 1)
	{
		p->s_a = (int *) malloc(sizeof(int) * argc);
		if (!p->s_a)
			exit(-1);
		p->s_b = (int *) malloc(sizeof(int) * argc);
		if (!p->s_b)
			exit(-1);
		ft_init_push(argc, argv, p);
	}
	else
		exit (0);
}

int	main(int argc, char **argv)
{
	t_push	p;

	ft_check_args(argc, argv, &p);
	// ft_show_stacks(&p);
	if (p.n == 2)
		if (*p.s_a > *(p.s_a + 1))
			ft_swap_a(&p);
	while (!ft_is_ordered(&p) || p.id_b < p.n)
	{
		ft_think(&p);
	}
	// ft_show_stacks(&p);
	ft_clean_push(&p);
	exit(0);
}
