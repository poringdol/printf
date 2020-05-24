#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int	ft_putnstr(char const *s, int n)
{
	int		i;
	i = 0;
	while (i < n)
	{
		if (write(1, &s[i], 1))
			i++;
	}
	return (n);
}

int print_null(t_flags *flags)
{
	int spaces;
	int len;

	len = ft_strlen("(null)");
	if (f_dot && f_dot_l < len)
		len = f_dot_l;
	spaces = f_spaces_l - len;
	if (f_spaces_l)
		return (f_minus ? (ft_putnstr("(null)", len) + print_spaces(spaces, ' ')) :
		print_spaces(spaces, ' ') + ft_putnstr("(null)", len));
	return (ft_putnstr("(null)", len));
}

int		print_s(va_list *ap, t_flags *flags)
{
	int		len;
	int		spaces;
	char 	*string;

	if(!(string = va_arg(*ap, char *)))
		return (print_null(flags));
	if (f_dot)
		len = (f_dot_l < (int)ft_strlen(string) ? f_dot_l : ft_strlen(string));
	else
		len = ft_strlen(string);
	spaces = f_spaces_l - len;
	return (f_minus ? (ft_putnstr(string, len) + print_spaces(spaces, ' ')) :
	print_spaces(spaces, ' ') + ft_putnstr(string, len));
}