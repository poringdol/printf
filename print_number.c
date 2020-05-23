#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

static int		print_space(t_flags *flags, int len)
{
	int	i;
	int space;

	i = 0;
	if (f_spaces_l > f_dot_l)
	{
		space = f_spaces_l - ((f_dot_l > len) ? f_dot_l : len);
		space -= (f_sign && f_dot && f_dot_l >= len) ? 1 : 0;
		while (i < space)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (f_zero_l > f_dot_l)
	{
		space = f_zero_l - ((f_dot_l ) ? f_dot_l : len);
		while (i < f_zero_l - f_dot_l - len)
		{
			ft_putchar('0');
			i++;
		}
	}
	return (i);
}

static int		plus_minus(t_flags *flags, int n)
{
	if (!n && !(f_zero_l) && ((f_dot && !(f_dot_l)) ||
	(f_minus && !(f_spaces_l)) || (f_plus && !(f_spaces_l))))
		return (0);
	if (f_plus && n >= 0)
		return (ft_putchar('+'));
	if (f_hidden && n >= 0)
		return (ft_putchar(' '));
	if (n < 0)
		return (ft_putchar('-'));
	return (0);
}

static int		print_dot(t_flags *flags, int len)
{
	int	i;
	int	dot;

	i = 0;
	dot = f_dot_l - len;
	if (f_sign)
		dot++;
	// if (f_dot_l > f_spaces_l)
	// {
		while (i < dot)
		{
			ft_putchar('0');
			i++;
		}
	// }
	return (i);
}

static int		put_number(int n)
{
	if (n == INT_MIN)
		return (ft_putstr("2147483648"));
	if (n >= 0)
		return (ft_putnbr(n));
	else
		return (ft_putnbr(-n));
	
}

static int		print_sign(t_flags *flags)
{
	int len;
	int res;

	if (!f_spaces_l && !f_zero_l && !f_plus && !f_hidden)
		return (0);
	res = 0;
	len = f_sign ? 1 : 0;
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += f_plus ? ft_putchar('+') : ft_putchar(' ');
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}

int				print_number(va_list *ap, t_flags *flags)
{
	int	n;
	int	len;
	int	res;

	res = 0;
	f_sign += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	f_intzero = (n == 0) ? 1 : 0;
	if (!n && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += plus_minus(flags, n);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}

int				print_unumber(va_list *ap, t_flags *flags)
{
	int	n;
	int	len;
	int	res;

	res = 0;
	n = va_arg(*ap, int);
	if (!n && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	res += ft_putunbr(n);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}