#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int		islongshort(va_list *ap, t_flags *flags, char **str)
{
	while (**str == 'l')
		set_flags(ap, flags, str);
	while (**str == 'h')
		set_flags(ap, flags, str);
	return (print_number(ap, flags, **str));
}

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u' || c == 'x' || c == 'X' || c == 'l' || c == 'h' || c == 'p')
		return (c);
	return (0);
}

int		isflags(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '*' || c == '#' || c == ' ' || c == '+' || ft_isdigit(c))
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

	n = 0;
	reset_flags(flags);
	while (!isspecs(**str) && isflags(**str))
		set_flags(ap, flags, str);
	if (**str == '%')
		return (print_percent(flags));
	if (**str == 'c')
		n = print_c(ap, flags);
	else if (**str == 's')
		n = print_s(ap, flags);
	else if (**str == 'i' || **str == 'd' || **str == 'u')
		n = print_number(ap, flags, **str);
	else if (**str == 'x' || **str == 'X')
		n = print_number(ap, flags, **str);
	else if (**str == 'l' || **str == 'h')
		n = islongshort(ap, flags, str);
	else if (**str == 'p')
		n = print_p(ap, flags);
	return (n);
}