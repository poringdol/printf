#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

int len_number(t_flags *flags, long long n)
{
	long long	i;
	long long	tmp;
	int			len;

	len = !flags->sign ? 0 : 1;
	if (n == LLONG_MIN)
		return (19);
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
    {
		if (i * 10 < i)
			return (19);
		i *= 10;
        len++;
    }
    return (n ? len : ++len);
}