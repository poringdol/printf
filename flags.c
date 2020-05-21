#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

t_flags *create_flags(void)
{
	t_flags *flags;

	if (!(flags = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->spaces_len = 0;
	flags->zero_len = 0;
	flags->dot_len = 0;
    return (flags);
}

void	set_flags(va_list *ap, t_flags *flags, char **c, int **last_flag)
{
	if (**c == '-')
		flags->minus = 1;
	else if (**c == '0' && !*last_flag)
	{
		flags->zero = 1;
		*last_flag = &(flags->zero_len);
	}
	else if (**c == '.')
	{
		flags->dot = 1;
		*last_flag = &(flags->dot_len);
	}
	else if (**c == '*' || ft_isdigit(**c))
	{
		if (*last_flag)
			**last_flag = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		else
			flags->spaces_len = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		*last_flag = NULL;
	}
    (*c)++;
}

void reset_flags(t_flags *flags)
{
    flags->minus = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->spaces_len = 0;
	flags->zero_len = 0;
	flags->dot_len = 0;
}