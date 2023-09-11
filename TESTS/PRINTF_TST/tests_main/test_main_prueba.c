#include <limits.h>
#include "../../../PRINTF/ft_printf.h"

int main(void)
{
    printf("Hola mundo %#sAdios\n", NULL);
    ft_printf("hola Mundo %#sAdios", NULL);
}