#include <limits.h>
#include <stddef.h>
#include "../../../PRINTF/ft_printf.h"

int	main(void)
{
	static char *s_hidden = "hi low\0don't print me lol\0";
	static unsigned int ncm_p = 1234;
	static unsigned int free = 42;
	static unsigned int malloc = -42;
	static unsigned int strlen = 12313;
	printf("%.p, %.0p", 0, 0);
	printf("{%10d}", 42);
	printf("{%4d}", 10000);
	printf("{%30d}", 10000);
	printf("{%10d}", -42);
	printf("{%3c}", 0);
	printf("{%5p}", 0);
	printf("{%-15p}", 0);
	printf("{%-13p}", &strlen);
	printf("{%-12p}", &strlen);
	printf("%s%p%d%d%p%s%p%p%s", "a", &free, 1, 2, &malloc, "b", &free, &malloc, "c");
	printf("%+u", 5);
	printf("%+u", 5);
	printf("%+u", 4294967295);
	printf("%+5u", 35);
	printf("%+7u", 0);
	printf("%+24u", 4294967295);
	printf("%+.7u", 234);
	printf("%+.3u", 3723);
	printf("%+05u", 432);
	printf("%+04u", 0);
	printf("%+8.5u", 34);
	printf("%+8.5u", 0);
	printf("%+8.3u", 8375);
	printf("%+3.7u", 3267);
	printf("%+3.3u", 6983);
	printf("%+-8.5u", 34);
	printf("%+-8.5u", 0);
	printf("%+-8.3u", 8375);
	printf("%+-3.7u", 3267);
	printf("%+-3.3u", 6983);
	printf("%0+8.5u", 34);
	printf("%0+8.5u", 0);
	printf("%0+8.3u", 8375);
	printf("%0+3.7u", 3267);
	printf("%0+3.3u", 6983);
	printf("%0+-8.5u", 34);
	printf("%0+-8.5u", 0);
	printf("%0+-8.3u", 8375);
	printf("%0+-3.7u", 3267);
	printf("%0+-3.3u", 6983);
	printf("%+X", 42);
	printf("% X", 42);
	printf("%+x", 42);
	printf("% x", 42);
	printf("%#u", 42);
	printf("%+u", 42);
	printf("% u", 42);
	printf("%#p", &ncm_p);
	printf("%+p", &ncm_p);
	printf("%+p", &ncm_p);
	printf("% p", &ncm_p);
	printf("% p", &ncm_p);
	printf("%s", s_hidden);
	printf("%3s", s_hidden);
	printf("%9s", s_hidden);
	printf("%.s", s_hidden);
	printf("%.9s", s_hidden);
	printf("%.03s", s_hidden);
	printf("%.09s", s_hidden);
	printf("1.%.03s", NULL);
	printf("2.%.09s", NULL);
	printf("3.%.00s", "\0");
	printf("4.%.01s", "\0");
	printf("5.%.03s", "\0");
	printf("6.%.09s", "\0");
	printf("7.%3.s", s_hidden);
	printf("8.%10.s", s_hidden);
	printf("9.%3.s", NULL);
	printf("10.%10.s", NULL);
	printf("11.%1.s", "\0");
	printf("12.%2.s", "\0");
	printf("13.%9.s", "\0");
	printf("14.%-3.s", s_hidden);
	printf("15.%-8.s", s_hidden);
	printf("16.%-3.s", NULL);
	printf("17.%-8.s", NULL);
	printf("18.%-1.s", "\0");
	printf("19.%-2.s", "\0");
	printf("20.%-6.s", "\0");
	printf("21.%3.1s", s_hidden);
	printf("22.%10.1s", s_hidden);
	printf("23.%3.1s", NULL);
	printf("24.%9.1s", NULL);
	printf("25.%-3.1s", s_hidden);
	printf("26.%-10.1s", s_hidden);
	printf("27.%-3.1s", NULL);
	printf("28.%-9.1s", NULL);
	printf("29.%-3.1s", "\0");
	printf("30.%-6.1s", "\0");
	printf("31.%3.6s", s_hidden);
	printf("32.%20.6s", s_hidden);
	printf("33.%3.6s", NULL);
	printf("34.%20.6s", NULL);
	printf("35.%3.6s", "\0");
	printf("36.%6.6s", "\0");
	printf("37.%-3.6s", s_hidden);
	printf("38.%-20.6s", s_hidden);
	printf("39.%-3.8s", s_hidden);
	printf("40.%-10.8s", s_hidden);
	printf("41.%-3.8s", NULL);
	printf("42.%-10.8s", NULL);
	printf("43.%-.00s", s_hidden);
	printf("44.%-.09s", s_hidden);
	printf("45.%+- 06.06s", s_hidden);
	printf("46.% 0+-6.06s", s_hidden);
	printf("47.%0 +-6.06s", s_hidden);
	printf("48.%+-0 6.06s", s_hidden);
	printf("49.%-+ 06.06s", s_hidden);
	printf("50.% -+06.06s", s_hidden);
	printf("51.%+- 07.06s", s_hidden);
	printf("52.% 0+-8.06s", s_hidden);
	printf("53.%0 +-9.06s", s_hidden);
	printf("54.%+-0 10.06s", s_hidden);
	printf("55.%-+ 011.06s", s_hidden);
	printf("56.% -+012.06s", s_hidden);
	printf("57.%+- 06.04s", s_hidden);
	printf("58.% 0+-6.04s", s_hidden);
	printf("59.%0 +-6.04s", s_hidden);
	printf("60.%+-0 6.04s", s_hidden);
	printf("61.%-+ 06.04s", s_hidden);
	printf("62.% 0-+6.04s", s_hidden);
	printf("63.%+- 06.09s", s_hidden);
	printf("64.% 0+-6.09s", s_hidden);
	printf("65.%0 +-6.09s", s_hidden);
	printf("66.%+-0 6.09s", s_hidden);
	printf("67.%-+ 06.09s", s_hidden);
	printf("68.% 0-+6.09s", s_hidden);
	printf("69.%+03s", s_hidden);
	printf("70.%+09s", s_hidden);
	printf("71.%+ 3s", s_hidden);
	printf("72.%+ 6s", s_hidden);
	printf("73.%00s", s_hidden);
	printf("74.%000s", s_hidden);
	printf("75.%0000s", s_hidden);
	printf("76.%-00s", s_hidden);
	printf("77.%0-0s", s_hidden);
	printf("78.%00-s", s_hidden);
	printf("79.%03s", s_hidden);
	printf("80.%09s", s_hidden);
	printf("81.%-03s", s_hidden);
	printf("82.%-09s", s_hidden);
	printf("\n\nStarting\n\n");
	ft_printf("%.p, %.0p", 0, 0);
	ft_printf("{%10d}", 42);
	ft_printf("{%4d}", 10000);
	ft_printf("{%30d}", 10000);
	ft_printf("{%10d}", -42);
	ft_printf("{%3c}", 0);
	ft_printf("{%5p}", 0);
	ft_printf("{%-15p}", 0);
	ft_printf("{%-13p}", &strlen);
	ft_printf("{%-12p}", &strlen);
	ft_printf("%s%p%d%d%p%s%p%p%s", "a", &free, 1, 2, &malloc, "b", &free, &malloc, "c");
	ft_printf("%+u", 5);
	ft_printf("%+u", 5);
	ft_printf("%+u", 4294967295);
	ft_printf("%+5u", 35);
	ft_printf("%+7u", 0);
	ft_printf("%+24u", 4294967295);
	ft_printf("%+.7u", 234);
	ft_printf("%+.3u", 3723);
	ft_printf("%+05u", 432);
	ft_printf("%+04u", 0);
	ft_printf("%+8.5u", 34);
	ft_printf("%+8.5u", 0);
	ft_printf("%+8.3u", 8375);
	ft_printf("%+3.7u", 3267);
	ft_printf("%+3.3u", 6983);
	ft_printf("%+-8.5u", 34);
	ft_printf("%+-8.5u", 0);
	ft_printf("%+-8.3u", 8375);
	ft_printf("%+-3.7u", 3267);
	ft_printf("%+-3.3u", 6983);
	ft_printf("%0+8.5u", 34);
	ft_printf("%0+8.5u", 0);
	ft_printf("%0+8.3u", 8375);
	ft_printf("%0+3.7u", 3267);
	ft_printf("%0+3.3u", 6983);
	ft_printf("%0+-8.5u", 34);
	ft_printf("%0+-8.5u", 0);
	ft_printf("%0+-8.3u", 8375);
	ft_printf("%0+-3.7u", 3267);
	ft_printf("%0+-3.3u", 6983);
	ft_printf("%+X", 42);
	ft_printf("% X", 42);
	ft_printf("%+x", 42);
	ft_printf("% x", 42);
	ft_printf("%#u", 42);
	ft_printf("%+u", 42);
	ft_printf("% u", 42);
	ft_printf("%#p", &ncm_p);
	ft_printf("%+p", &ncm_p);
	ft_printf("%+p", &ncm_p);
	ft_printf("% p", &ncm_p);
	ft_printf("% p", &ncm_p);
	ft_printf("%s", s_hidden);
	ft_printf("%3s", s_hidden);
	ft_printf("%9s", s_hidden);
	ft_printf("%.s", s_hidden);
	ft_printf("%.9s", s_hidden);
	ft_printf("%.03s", s_hidden);
	ft_printf("%.09s", s_hidden);
	ft_printf("1.%.03s", NULL);
	ft_printf("2.%.09s", NULL);
	ft_printf("3.%.00s", "\0");
	ft_printf("4.%.01s", "\0");
	ft_printf("5.%.03s", "\0");
	ft_printf("6.%.09s", "\0");
	ft_printf("7.%3.s", s_hidden);
	ft_printf("8.%10.s", s_hidden);
	ft_printf("9.%3.s", NULL);
	ft_printf("10.%10.s", NULL);
	ft_printf("11.%1.s", "\0");
	ft_printf("12.%2.s", "\0");
	ft_printf("13.%9.s", "\0");
	ft_printf("14.%-3.s", s_hidden);
	ft_printf("15.%-8.s", s_hidden);
	ft_printf("16.%-3.s", NULL);
	ft_printf("17.%-8.s", NULL);
	ft_printf("18.%-1.s", "\0");
	ft_printf("19.%-2.s", "\0");
	ft_printf("20.%-6.s", "\0");
	ft_printf("21.%3.1s", s_hidden);
	ft_printf("22.%10.1s", s_hidden);
	ft_printf("23.%3.1s", NULL);
	ft_printf("24.%9.1s", NULL);
	ft_printf("25.%-3.1s", s_hidden);
	ft_printf("26.%-10.1s", s_hidden);
	ft_printf("27.%-3.1s", NULL);
	ft_printf("28.%-9.1s", NULL);
	ft_printf("29.%-3.1s", "\0");
	ft_printf("30.%-6.1s", "\0");
	ft_printf("31.%3.6s", s_hidden);
	ft_printf("32.%20.6s", s_hidden);
	ft_printf("33.%3.6s", NULL);
	ft_printf("34.%20.6s", NULL);
	ft_printf("35.%3.6s", "\0");
	ft_printf("36.%6.6s", "\0");
	ft_printf("37.%-3.6s", s_hidden);
	ft_printf("38.%-20.6s", s_hidden);
	ft_printf("39.%-3.8s", s_hidden);
	ft_printf("40.%-10.8s", s_hidden);
	ft_printf("41.%-3.8s", NULL);
	ft_printf("42.%-10.8s", NULL);
	ft_printf("43.%-.00s", s_hidden);
	ft_printf("44.%-.09s", s_hidden);
	ft_printf("45.%+- 06.06s", s_hidden);
	ft_printf("46.% 0+-6.06s", s_hidden);
	ft_printf("47.%0 +-6.06s", s_hidden);
	ft_printf("48.%+-0 6.06s", s_hidden);
	ft_printf("49.%-+ 06.06s", s_hidden);
	ft_printf("50.% -+06.06s", s_hidden);
	ft_printf("51.%+- 07.06s", s_hidden);
	ft_printf("52.% 0+-8.06s", s_hidden);
	ft_printf("53.%0 +-9.06s", s_hidden);
	ft_printf("54.%+-0 10.06s", s_hidden);
	ft_printf("55.%-+ 011.06s", s_hidden);
	ft_printf("56.% -+012.06s", s_hidden);
	ft_printf("57.%+- 06.04s", s_hidden);
	ft_printf("58.% 0+-6.04s", s_hidden);
	ft_printf("59.%0 +-6.04s", s_hidden);
	ft_printf("60.%+-0 6.04s", s_hidden);
	ft_printf("61.%-+ 06.04s", s_hidden);
	ft_printf("62.% 0-+6.04s", s_hidden);
	ft_printf("63.%+- 06.09s", s_hidden);
	ft_printf("64.% 0+-6.09s", s_hidden);
	ft_printf("65.%0 +-6.09s", s_hidden);
	ft_printf("66.%+-0 6.09s", s_hidden);
	ft_printf("67.%-+ 06.09s", s_hidden);
	ft_printf("68.% 0-+6.09s", s_hidden);
	ft_printf("69.%+03s", s_hidden);
	ft_printf("70.%+09s", s_hidden);
	ft_printf("71.%+ 3s", s_hidden);
	ft_printf("72.%+ 6s", s_hidden);
	ft_printf("73.%00s", s_hidden);
	ft_printf("74.%000s", s_hidden);
	ft_printf("75.%0000s", s_hidden);
	ft_printf("76.%-00s", s_hidden);
	ft_printf("77.%0-0s", s_hidden);
	ft_printf("78.%00-s", s_hidden);
	ft_printf("79.%03s", s_hidden);
	ft_printf("80.%09s", s_hidden);
	ft_printf("81.%-03s", s_hidden);
	ft_printf("82.%-09s", s_hidden);
	return (0);
}