#include <limits.h>
#include "../../../PRINTF/ft_printf.h"

int	main(void)
{
	printf("1. %-+.0p, %.p", 0, 0);
	printf("2. %-+# 010.5p", 0);
	printf("3. %-+#9.2p", 1234);
	printf("4. %-+#9.2p", 1234567);
	printf("5. %-+#2.9p", 1234);
	printf("6. %-+2.9p", 1234567);

	printf("\n\nStarting\n\n");

	ft_printf("1. %-+.0p, %.p", 0, 0);
	ft_printf("2. %-+# 010.5p", 0);
	ft_printf("3. %-+9.2p", 1234);
	ft_printf("4. %-+9.2p", 1234567);
	ft_printf("5. %-+2.9p", 1234);
	ft_printf("6. %-+2.9p", 1234567);
	return (0);
}