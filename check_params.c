#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u' || c == 'x' || c == 'X' || c == 'l')
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
	int		*last_flag;

	n = 0;
	last_flag = NULL;
	reset_flags(flags);
	if (**str == '%')
		return (ft_putchar(**str));
	while (!isspecs(**str) && isflags(**str))
		set_flags(ap, flags, str, &last_flag);
	if (**str == 'c')
		n = print_c(ap, flags);
	else if (**str == 's')
		n = print_s(ap, flags);
	else if (**str == 'i' || **str == 'd' || **str == 'u')
		n = print_number(ap, flags, **str);
	else if (**str == 'x' || **str == 'X')
		n = print_number(ap, flags, **str);
	else if (**str == 'l')
		set_flags(ap, flags, str, &last_flag);
	return (n);
}