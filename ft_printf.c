#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int ft_printf(const char *format, ...)
{
	va_list ap;
	t_flags	*flags;
	int		flag;
	int		n;

	va_start(ap, format);
	n = 0;
	flag = 0;
	flags = create_flags();
	while (*format)
	{
		if (*format == '%' && !flag)
			flag = 1;
		else if (*format != '%' && !flag)
			n += write(1, format, 1);
		else if (flag)
		{
			n += check_params((char **)&format, &ap, flags);
			flag = 0;
		}
		format++;
	}
	free(flags);
	va_end(ap);
	return (n);
}