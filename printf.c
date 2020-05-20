#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

#include <stdio.h>

size_t	print_string(char *string)
{
	ft_putstr(string);
	return (ft_strlen(string));
}

int	print_number(int number)
{
	int n;

	n = number < 0 ? 2 : 1;
	ft_putnbr(number);
	while ((number /= 10) != 0)
		n++;
	return (n);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	char	*str;
	int		n;
	int		flag;

	va_start(ap, format);
	str = (char *)format;
	n = 0;
	flag = 0;
	while (*str)
	{
		if (*str == '%' && !flag)
			flag = 1;
		else if (*str != '%' && !flag)
			n += write(1, str, 1);
		else if (flag)
		{
			n += check_params(&str, &ap);
			flag = 0;
		}
		str++;
	}
	va_end(ap);
	return (n);
}