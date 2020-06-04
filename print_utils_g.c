#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

void	float_gparams(char buf[D_SIZE])
{
    int i;

	i = ft_strlen(buf) - 1;
	while (i && (buf[i] == '0' || buf[i] == '.'))
	{
		if (buf[i] == '.')
		{
			buf[i] = 0;
			return ;
		} 
		buf[i] = 0;
		i--;
	}
}