#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

static int		print_space(t_flags *flags, int len)
{
	int i;

	i = 0;
	while ((i < flags->spaces_len - flags->dot_len) && (i < len))
	{
		ft_putchar(' ');
		i++;
	}

	while (i++ < len)
		ft_putchar('0');
	return (len > 0 ? len : 0);
}


int len_number(t_flags *flags, int n)
{
	long long	i;
	int			tmp;
	int			len;

	if (n == INT_MIN)
		return (11);
	len = n >= 0 && !(flags->plus) && !(flags->hidden) ? 0 : 1;
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
		i *= 10;
	if (tmp != 0)
		i /= 10;
	while (i > 0)
	{
		tmp %= i;
		i /= 10;
		len++;
	}
    return (len);
}

int			put_number(int n)
{
	if (n == INT_MIN)
		return (ft_putstr("2147483648"));
	if (n >= 0)
		return (ft_putnbr(n));
	else
		return (ft_putnbr(-n));
}

static int	plus_minus(t_flags *flags, int n)
{
	if (!n && !(flags->zero_len) && ((flags->dot && !(flags->dot_len)) ||
	(flags->minus && !(flags->spaces_len)) || (flags->plus && !(flags->spaces_len))))
		return (0);
	if (flags->plus && n >= 0)
		return (ft_putchar('+'));
	if (flags->hidden && n >= 0)
		return (ft_putchar(' '));
	if (n < 0)
		return (ft_putchar('-'));
	return (0);
}

int print_number(va_list *ap, t_flags *flags)
{
	int n;
	int len;

	n = va_arg(*ap, int);
	if (!n && ((flags->dot && !(flags->dot_len)) || (flags->minus && !flags->spaces_len)))
		return (plus_minus(flags, n) + print_space(flags, flags->spaces_len));
	if (flags->dot && !(flags->dot_len) && !n)
		return (print_space(flags, flags->spaces_len) + plus_minus(flags, n));
	len = len_number(flags, n);
	if (flags->dot && flags->dot_len > flags->spaces_len)
		return (plus_minus(flags, n) + print_space(flags, flags->dot_len - len +
		(n < 0 || flags->plus || flags->hidden)) + put_number(n));
	if (flags->zero)
		return (plus_minus(flags, n) + print_space(flags, flags->zero_len - len) + put_number(n));
	if (flags->minus)
		return (plus_minus(flags, n) + put_number(n) + print_space(flags, flags->spaces_len - len));
	if (flags->spaces_len)
		return (print_space(flags, flags->spaces_len - len) + plus_minus(flags, n) + put_number(n));
	return (plus_minus(flags, n) + put_number(n));
}