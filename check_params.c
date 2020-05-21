#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"
#include "libft.h"

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd')
		return (c);
	return (0);
}

int		print_spaces(int n, int c)
{
	int i;

	i = 0;
	while (i++ < n)
		ft_putchar(c);
	return (n > 0 ? n : 0);
}

int get_number(char **arr)
{
	int		k;
	char	*tmp;
	char	str[12];

	k = 0;
	tmp = *arr;
	while (*tmp && ft_isdigit(*tmp))
		str[k++] = *tmp++;
	str[k] = '\0';
	*arr = --tmp;
	return (ft_atoi(str));
}

int 	check_params(char **str, va_list *ap, t_flags *flags)
{
	int		n;
	int		*last_flag;
	char	*tmp;

	n = 0;
	last_flag = NULL;
	tmp = *str;
	reset_flags(flags);
	if (*tmp == '%')
		return (ft_putchar(*tmp++));
	while (!isspecs(*tmp))
		set_flags(ap, flags, &tmp, &last_flag);
	if (*tmp == 'c')
		n = print_char(ap, flags);
	else if (*tmp == 's')
		n = print_string(ap, flags);
	else if (*tmp == 'i' || *tmp == 'd')
		n = print_number(ap, flags);
	*str = tmp;
	return (n);
}