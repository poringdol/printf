#include "libft.h"
#include <stdio.h>

void ft_printf(void)
{
	char *buf1 = "big";
	char *buf2 = "boobs";
	char *boobs = ft_strjoin(buf1, buf2);
	printf("%s\n", boobs);
}