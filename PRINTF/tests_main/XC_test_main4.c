#include <limits.h>

int	main(void)
{
	printf("%.0p, %.p", 0, 0);
	printf("%.5p", 0);
	printf("%9.2p", 1234);
	printf("%9.2p", 1234567);
	printf("%2.9p", 1234);
	printf("%2.9p", 1234567);

	printf("\n\nStarting\n\n");

	ft_printf("%.0p, %.p", 0, 0);
	ft_printf("%.5p", 0);
	ft_printf("%9.2p", 1234);
	ft_printf("%9.2p", 1234567);
	ft_printf("%2.9p", 1234);
	ft_printf("%2.9p", 1234567);
	return (0);
}