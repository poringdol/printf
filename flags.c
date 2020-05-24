#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static void	set_last(t_flags *flags, int c)
{
	if (c == '0' && !f_last_f)
	{
		flags->zero = 1;
		f_last_f = &(flags->zero_len);
	}
	else if (c == '.')
	{
		flags->dot = 1;
		f_last_f = &(flags->dot_len);
	}
	else if (c == '-')
	{
		if (f_last_f == &(flags->zero_len))
		{
			flags->zero = 0;
			f_last_f = NULL;
			flags->spaces_len = (!flags->spaces_len && flags->zero_len) ?
			flags->zero_len : flags->spaces_len;
		}
		flags->minus = 1;
	}
}

t_flags		*create_flags(void)
{
	t_flags *flags;

	if (!(flags = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	flags->minus = 0;
	flags->plus = 0;
	flags->hidden = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->spaces_len = 0;
	flags->zero_len = 0;
	flags->dot_len = 0;
	flags->sign = 0;
	flags->intzero = 0;
	flags->ll = 0;
	flags->hh = 0;
	flags->hex = 0;
	flags->last_flag = NULL;
	return (flags);
}

void		set_flags(va_list *ap, t_flags *flags, char **c)
{
	if (**c == '-')
		set_last(flags, **c);
	else if (**c == '+')
		flags->plus = 1;
	else if (**c == ' ')
		flags->hidden = 1;
	else if (**c == '0' && !f_last_f && !flags->minus)
		set_last(flags, **c);
	else if (**c == '.')
		set_last(flags, **c);
	else if (**c == '*' || ft_isdigit(**c))
	{
		if (f_last_f)
			*f_last_f = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		else
			flags->spaces_len = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		f_last_f = NULL;
	}
	else if (**c == 'l')
		flags->ll++;
	else if (**c == 'h')
		flags->hh++;
	else if (**c == '#')
		flags->hash = 1;
	(*c)++;
}

void		reset_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->plus = 0;
	flags->hidden = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->spaces_len = 0;
	flags->zero_len = 0;
	flags->dot_len = 0;
	flags->sign = 0;
	flags->intzero = 0;
	flags->ll = 0;
	flags->hh = 0;
	flags->hex = 0;
	flags->hash = 0;
	flags->last_flag = NULL;
}

void		ignored_flag(t_flags *flags)
{
	if (flags->plus)
		flags->hidden = 0;
	if (flags->minus)
		flags->zero = 0;
	if (flags->dot && flags->zero)
	{
		flags->spaces_len = flags->zero_len;
		flags->zero_len = 0;
		flags->zero = 0;
	}
	if (flags->plus || flags->hidden)
		flags->sign = 1;
	if (flags->hash && flags->intzero)
		flags->hash = 0;
	if (flags->hash && !flags->intzero && f_dot)
		flags->dot_len += 2;
}