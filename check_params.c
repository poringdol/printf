#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u')
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
		return (ft_putchar(*((*str)++)));
	while (!isspecs(**str))
		set_flags(ap, flags, str, &last_flag);
	ignored_flag(flags);
	if (**str == 'c')
		n = print_char(ap, flags);
	else if (**str == 's')
		n = print_string(ap, flags);
	else if (**str == 'i' || **str == 'd')
		n = print_number(ap, flags);
	else if (**str == 'u')
		n = print_unumber(ap, flags);
	else
		n = ft_putchar(**str);
	return (n);
}