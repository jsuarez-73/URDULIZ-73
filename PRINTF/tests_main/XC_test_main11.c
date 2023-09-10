#include <limits.h>
#include <stddef.h>

int	main(void)
{
	printf("%.p", NULL);
	printf("%.d", 1);
	printf("%.d", 0);
	printf("%.u", 1);
	printf("%.s", "aasf");
	printf("%.p", NULL);
	printf("%.c", 'a');
	printf("%.x", 0xee);
	printf("%.X", 0xee);
	printf("%1.p", NULL);
	printf("%1.d", 1);
	printf("%1.u", 1);
	printf("%1.s", "aasf");
	printf("%1.p", NULL);
	printf("%1.c", 'a');
	printf("%1.x", 0xee);
	printf("%1.X", 0xee);
	printf("%5.p", NULL);
	printf("%5.d", 1);
	printf("%5.u", 1);
	printf("%5.s", "aasf");
	printf("%5.p", NULL);
	printf("%5.c", 'a');
	printf("%5.x", 0xee);
	printf("%5.X", 0xee);
	printf("-->|%-16.p|<-- ", NULL);
	printf("-->|%-16p|<-- ",  (void*)0x1900);
	printf("-->|%-16.p|<-- ", NULL);
	printf("-->|%-16p|<-- ",  (void*)0x1900);
	printf("%.0p", NULL);
	printf("%.2p", NULL);
	printf("%.3p", NULL);
	printf("%.4p", NULL);
	printf("%.5p", NULL);
	printf("%.6p", NULL);
	printf("%.7p", NULL);

	printf("\n\nStarting\n\n");

	ft_printf("%.p", NULL);
	ft_printf("%.d", 1);
	ft_printf("%.d", 0);
	ft_printf("%.u", 1);
	ft_printf("%.s", "aasf");
	ft_printf("%.p", NULL);
	ft_printf("%.c", 'a');
	ft_printf("%.x", 0xee);
	ft_printf("%.X", 0xee);
	ft_printf("%1.p", NULL);
	ft_printf("%1.d", 1);
	ft_printf("%1.u", 1);
	ft_printf("%1.s", "aasf");
	ft_printf("%1.p", NULL);
	ft_printf("%1.c", 'a');
	ft_printf("%1.x", 0xee);
	ft_printf("%1.X", 0xee);
	ft_printf("%5.p", NULL);
	ft_printf("%5.d", 1);
	ft_printf("%5.u", 1);
	ft_printf("%5.s", "aasf");
	ft_printf("%5.p", NULL);
	ft_printf("%5.c", 'a');
	ft_printf("%5.x", 0xee);
	ft_printf("%5.X", 0xee);
	ft_printf("-->|%-16.p|<-- ", NULL);
	ft_printf("-->|%-16p|<-- ",  (void*)0x1900);
	ft_printf("-->|%-16.p|<-- ", NULL);
	ft_printf("-->|%-16p|<-- ",  (void*)0x1900);
	ft_printf("%.0p", NULL);
	ft_printf("%.2p", NULL);
	ft_printf("%.3p", NULL);
	ft_printf("%.4p", NULL);
	ft_printf("%.5p", NULL);
	ft_printf("%.6p", NULL);
	ft_printf("%.7p", NULL);
	return (0);
}