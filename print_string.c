#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

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
	char	*print;

	string = va_arg(*ap, char *);
	print = string ? string : "(null)";

	if (flags->dot)
		len = (flags->dot_len < (int)ft_strlen(print) ? flags->dot_len : ft_strlen(print));
	else
		len = ft_strlen(print);
	spaces = flags->spaces_len - len;
	return (flags->minus ? (ft_putnstr(print, len) + print_spaces(spaces)) :
	print_spaces(spaces) + ft_putnstr(print, len));
}