#include <limits.h>

int	main()
{
	printf("%c", '0');
	printf(" %c ", '0');
	printf(" %c", '0' - 256);
	printf("%c ", '0' + 256);
	printf(" %c %c %c ", '0', 0, '1');
	printf(" %c %c %c ", ' ', ' ', ' ');
	printf(" %c %c %c ", '1', '2', '3');
	printf(" %c %c %c ", '2', '1', 0);
	printf(" %c %c %c ", 0, '1', '2');
	printf("Starting...\n");
	ft_printf("%c", '0');
	ft_printf(" %c ", '0');
	ft_printf(" %c", '0' - 256);
	ft_printf("%c ", '0' + 256);
	ft_printf(" %c %c %c ", '0', 0, '1');
	ft_printf(" %c %c %c ", ' ', ' ', ' ');
	ft_printf(" %c %c %c ", '1', '2', '3');
	ft_printf(" %c %c %c ", '2', '1', 0);
	ft_printf(" %c %c %c ", 0, '1', '2');
	return (0);
}