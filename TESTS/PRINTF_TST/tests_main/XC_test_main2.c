#include <limits.h>
#include <stddef.h>
#include "../../../PRINTF/ft_printf.h"

int	main(void)
{
	printf("hello, world!");
	printf("");
	printf("\t\n\r\v\f\n");
	printf("1.%%");
	printf("2.%5%");
	printf("3.%-5%");
	printf("4.%05%");
	printf("5.%-05.4%");
	printf("6.%+u", 5);
	printf("7.%+u", 5);
	printf("8.%+u", 4294967295);
	printf("9.%+5u", 35);
	printf("10.%+7u", 0);
	printf("11.%+24u", 4294967295);
	printf("12.%+.7u", 234);
	printf("13.%+.3u", 3723);
	printf("14.%+05u", 432);
	printf("15.%+04u", 0);
	printf("16.%+8.5u", 34);
	printf("17.%+8.5u", 0);
	printf("18.%+8.3u", 8375);
	printf("19.%+3.7u", 3267);
	printf("20.%+3.3u", 6983);
	printf("21.%+-8.5u", 34);
	printf("22.%+-8.5u", 0);
	printf("23.%+-8.3u", 8375);
	printf("24.%+-3.7u", 3267);
	printf("25.%+-3.3u", 6983);
	printf("26.%#0+8.5u", 34);
	printf("27.%#0+8.5u", 0);
	printf("28.%#0+8.3u", 8375);
	printf("29.%#0+3.7u", 3267);
	printf("30.%#0+3.3u", 6983);
	printf("31.%#0+-8.5u", 34);
	printf("32.%#0+-8.5u", 0);
	printf("33.%#0+-8.3u", 8375);
	printf("34.%#0+-3.7u", 3267);
	printf("35.%#0+-3.3u", 6983);
	printf("36.%-021s", "abc");
	printf("37.%-05s", "goes over");
	printf("38.%04.3s%-7.4s", "hello", "world");
	printf("39.%021s", NULL);
	printf("40.%02s", NULL);
	printf("41.%-021s", NULL);
	printf("42.%-03s", NULL);
	printf("43.%05c", '\0');
	printf("44.%-05c", '\0');
	printf("45.%.c", 'a');
	printf("46.%05c", 'a');
	printf("47.%0c", 'a');
	printf("48.% c", 'a');
	printf("49.% c", -42);
	printf("50.%-c", 'a');
	printf("51.%05s", "hello");
	printf("52.%0s", "hello");
	printf("53.%-s", "hello");

	printf("\n\nStarting\n\n");

	ft_printf("hello, world!");
	ft_printf("");
	ft_printf("\t\n\r\v\f\n");
	ft_printf("1.%%");
	ft_printf("2.%5%");
	ft_printf("3.%-5%");
	ft_printf("4.%05%");
	ft_printf("5.%-05.4%");
	ft_printf("6.%+u", 5);
	ft_printf("7.%+u", 5);
	ft_printf("8.%+u", 4294967295);
	ft_printf("9.%+5u", 35);
	ft_printf("10.%+7u", 0);
	ft_printf("11.%+24u", 4294967295);
	ft_printf("12.%+.7u", 234);
	ft_printf("13.%+.3u", 3723);
	ft_printf("14.%+05u", 432);
	ft_printf("15.%+04u", 0);
	ft_printf("16.%+8.5u", 34);
	ft_printf("17.%+8.5u", 0);
	ft_printf("18.%+8.3u", 8375);
	ft_printf("19.%+3.7u", 3267);
	ft_printf("20.%+3.3u", 6983);
	ft_printf("21.%+-8.5u", 34);
	ft_printf("22.%+-8.5u", 0);
	ft_printf("23.%+-8.3u", 8375);
	ft_printf("24.%+-3.7u", 3267);
	ft_printf("25.%+-3.3u", 6983);
	ft_printf("26.%#0+8.5u", 34);
	ft_printf("27.%#0+8.5u", 0);
	ft_printf("28.%#0+8.3u", 8375);
	ft_printf("29.%#0+3.7u", 3267);
	ft_printf("30.%#0+3.3u", 6983);
	ft_printf("31.%#0+-8.5u", 34);
	ft_printf("32.%#0+-8.5u", 0);
	ft_printf("33.%#0+-8.3u", 8375);
	ft_printf("34.%#0+-3.7u", 3267);
	ft_printf("35.%#0+-3.3u", 6983);
	ft_printf("36.%-021s", "abc");
	ft_printf("37.%-05s", "goes over");
	ft_printf("38.%04.3s%-7.4s", "hello", "world");
	ft_printf("39.%021s", NULL);
	ft_printf("40.%02s", NULL);
	ft_printf("41.%-021s", NULL);
	ft_printf("42.%-03s", NULL);
	ft_printf("43.%05c", '\0');
	ft_printf("44.%-05c", '\0');
	ft_printf("45.%.c", 'a');
	ft_printf("46.%05c", 'a');
	ft_printf("47.%0c", 'a');
	ft_printf("48.% c", 'a');
	ft_printf("49.% c", -42);
	ft_printf("50.%-c", 'a');
	ft_printf("51.%05s", "hello");
	ft_printf("52.%0s", "hello");
	ft_printf("53.%-s", "hello");
	return (0);
}