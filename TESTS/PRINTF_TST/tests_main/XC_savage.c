#include <limits.h>
#include "../../../PRINTF/ft_printf.h"

int main(void)
{
	printf("%24.6x%61.146u%059.u%p" ,3428759210u,699768298u,3551192901u,(void*)9281414673285757929lu);
	printf("%029.d%  10.8d%179.27s%c%198.3u" ,-144374035,630963439,"luU",-62,2133259791u);
	printf("%182p%66.x%-7.15s%-178.167u%071.i" ,(void*)16481877983539570083lu,1196899348u,"2d",2279048326u,-822789086);
	printf("%81.143s%-144.85X%-187.10s%113.139s%118.X" ,"L);N\vuiBYewse,qzL;23kr>",2587710503u,"Ink.<6*#vZA","\nw%@\rd\vw20!\fNM$\f>",4000484419u);
	printf("%92.149u%-9.71s% 196.85d%0+34.106d%0156.x" ,3788956531u,"84\t\n<'(\t|<\vrxRUJ|hZf5!boo=",-1906625592,1389229238,831533163u);
	printf("%0103.u%-118p%#195.159X%-41.93u" ,3613058636u,(void*)659322935771993792lu,460562733u,2054216390u);
	printf("%92c%-114.17u%0#130.X%-4.85i" ,-49,3809237023u,697920344u,1528796577);
	printf("%0 193.147i%3.39x%0168.X%0038.139x" ,-2067353245,2365913708u,1413712787u,260332660u);
	printf("%#140.24x%-50.132d%064.X%-19.166d" ,4190577632u,-259299223,3480388900u,143674384);
	printf("%76c%46.122x%+-125.57d%047.u%104.48i" ,-49,188975216u,415293253,1510723789u,629612043);
	printf("%-53p%  121.126d%0083.135i%185p%075.u" ,(void*)9550813173812264337lu,-227992850,719829262,(void*)5288247948920258925lu,53623191u);
	printf("%#126.117X%000144.i%-177.12d%-115.168x%020.u" ,1944698944u,474447862,-1391273338,1947550432u,3901810585u);
	printf("%#180x%0 142.d%+60.d%-122.25i" ,3179607536u,-708729510,1136972737,-769772092);
	
	printf("\n\n---------------------------------------Starting----------------------------------------\n\n");

	ft_printf("%24.6x%61.146u%059.u%p" ,3428759210u,699768298u,3551192901u,(void*)9281414673285757929lu);
	ft_printf("%029.d%  10.8d%179.27s%c%198.3u" ,-144374035,630963439,"luU",-62,2133259791u);
	ft_printf("%182p%66.x%-7.15s%-178.167u%071.i" ,(void*)16481877983539570083lu,1196899348u,"2d",2279048326u,-822789086);
	ft_printf("%81.143s%-144.85X%-187.10s%113.139s%118.X" ,"L);N\vuiBYewse,qzL;23kr>",2587710503u,"Ink.<6*#vZA","\nw%@\rd\vw20!\fNM$\f>",4000484419u);
	ft_printf("%92.149u%-9.71s% 196.85d%0+34.106d%0156.x" ,3788956531u,"84\t\n<'(\t|<\vrxRUJ|hZf5!boo=",-1906625592,1389229238,831533163u);
	ft_printf("%0103.u%-118p%#195.159X%-41.93u" ,3613058636u,(void*)659322935771993792lu,460562733u,2054216390u);
	ft_printf("%92c%-114.17u%0#130.X%-4.85i" ,-49,3809237023u,697920344u,1528796577);
	ft_printf("%0 193.147i%3.39x%0168.X%0038.139x" ,-2067353245,2365913708u,1413712787u,260332660u);
	ft_printf("%#140.24x%-50.132d%064.X%-19.166d" ,4190577632u,-259299223,3480388900u,143674384);
	ft_printf("%76c%46.122x%+-125.57d%047.u%104.48i" ,-49,188975216u,415293253,1510723789u,629612043);
	ft_printf("%-53p%  121.126d%0083.135i%185p%075.u" ,(void*)9550813173812264337lu,-227992850,719829262,(void*)5288247948920258925lu,53623191u);
	ft_printf("%#126.117X%000144.i%-177.12d%-115.168x%020.u" ,1944698944u,474447862,-1391273338,1947550432u,3901810585u);
	ft_printf("%#180x%0 142.d%+60.d%-122.25i" ,3179607536u,-708729510,1136972737,-769772092);
	return (0);
}