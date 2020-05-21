#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int print_null(t_flags *flags)
{
	int spaces;
	int len;

	len = ft_strlen("(null)");
	if (flags->dot && flags->dot_len < len && !flags->spaces_len)
		return (0);
	if (flags->dot && flags->dot_len < len)
		len = flags->dot_len;
	spaces = flags->spaces_len - len;
	if (flags->spaces_len)
	{
		if (flags->dot && flags->dot_len < (int)ft_strlen("(null)"))
			return (print_spaces(flags->spaces_len));
		else
			return (flags->minus ? (ft_putstr("(null)") + print_spaces(spaces)) :
			print_spaces(spaces) + ft_putstr("(null)"));
	}
	return (ft_putstr("(null)"));
}

int	ft_putnstr(char const *s, int n)
{
	int i;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	while (i < n)
	{
		if (write(1, &s[i], 1))
			i++;
	}
	return (n);
}

int		print_string(va_list *ap, t_flags *flags)
{
	int		len;
	int		spaces;
	char 	*string;

	if(!(string = va_arg(*ap, char *)))
		return (print_null(flags));
	if (flags->dot)
		len = (flags->dot_len < (int)ft_strlen(string) ? flags->dot_len : ft_strlen(string));
	else
		len = ft_strlen(string);
	spaces = flags->spaces_len - len;
	return (flags->minus ? (ft_putnstr(string, len) + print_spaces(spaces)) :
	print_spaces(spaces) + ft_putnstr(string, len));
}