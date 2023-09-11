#include <limits.h>
#include "../../../PRINTF/ft_printf.h"

int	main()
{
	printf(" %% ");
	printf(" %%%% ");
	printf(" %% %% %% ");
	printf(" %%  %%  %% ");
	printf(" %%   %%   %% ");
	printf("%%");
	printf("%% %%");
	printf("\nStarting...\n");
	ft_printf(" %% ");
	ft_printf(" %%%% ");
	ft_printf(" %% %% %% ");
	ft_printf(" %%  %%  %% ");
	ft_printf(" %%   %%   %% ");
	ft_printf("%%");
	ft_printf("%% %%\n");	
	return (0);
}