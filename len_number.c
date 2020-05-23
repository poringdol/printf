#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

int len_number(t_flags *flags, int n)
{
	long long	i;
	int			tmp;
	int			len;

	len = !flags->sign ? 0 : 1;
	if (n == INT_MIN)
		return (10);
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
    {
		i *= 10;
        len++;
    }
    return (n ? len : ++len);
}