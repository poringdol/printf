#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

static int		print_space(t_flags *flags, int len)
{
	int			i;
	int			space;

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
		space = f_zero_l - (f_dot_l ? f_dot_l : len);
		while (i < f_zero_l - f_dot_l - len)
		{
			ft_putchar('0');
			i++;
		}
	}
	return (i);
}

static int		plus_minus(t_flags *flags, long long n, int c)
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
	if (f_hash)
		return (c == 'x' ? ft_putstr("0x") : ft_putstr("0X"));
	return (0);
}

static int		print_dot(t_flags *flags, int len)
{
	int			i;
	int			dot;

	i = 0;
	dot = f_dot_l - len;
	if (f_sign)
		dot++;
	while (i < dot)
	{
		ft_putchar('0');
		i++;
	}
	return (i);
}

static int		put_number(long long n)
{
	if (n == LLONG_MIN)
		return (ft_putstr("9223372036854775808"));
	if (n >= 0)
		return (ft_putnbr(n));
	else
		return (ft_putnbr(-n));
	
}

static int		print_sign(t_flags *flags)
{
	int			len;
	int 		res;

	if (!f_spaces_l && !f_zero_l && !f_plus && !f_hidden)
		return (0);
	res = 0;
	len = f_sign ? 1 : 0;
	f_spaces_l -= (f_sign ? 0 : 1);
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

int				print_i(va_list *ap, t_flags *flags)
{
	int			n;
	int			len;
	int			res;

	res = 0;
	f_sign += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	f_intzero = (n == 0) ? 1 : 0;
	ignored_flag(flags);
	if (!n && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += plus_minus(flags, n, 0);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}

int				print_u(va_list *ap, t_flags *flags)
{
	int	n;
	int	len;
	int	res;

	res = 0;
	n = va_arg(*ap, int);
	ignored_flag(flags);
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

int				print_l(va_list *ap, t_flags *flags)
{
	long		n;
	int			len;
	int			res;

	res = 0;
	f_sign += (n = va_arg(*ap, long)) < 0 ? 1 : 0;
	f_intzero = (n == 0) ? 1 : 0;
	ignored_flag(flags);
	if (!n && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += plus_minus(flags, n, 0);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}

int				print_ll(va_list *ap, t_flags *flags)
{
	long long	n;
	int			len;
	int			res;

	res = 0;
	f_sign += (n = va_arg(*ap, long long)) < 0 ? 1 : 0;
	f_intzero = (n == 0) ? 1 : 0;
	ignored_flag(flags);
	if (!n && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += plus_minus(flags, n, 0);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	return (res);
}

char			*convert_x(va_list *ap, t_flags *flags, char c)
{ 
	int			j;
	unsigned	n;
	char		tmp;
	char 		*buf;
	
	j = 0;
	buf = (char *)ft_calloc(60, 1);
	if ((n = va_arg(*ap, long long)) < 0)
		buf[j++] = '-';
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 16 < 10) ? n % 16 + '0' : n % 16 - 10 + 'a';
		n /= 16;
	}
	j = (buf[0] == '-') ? 1 : 0;
	int len = (buf[0] == '-') ? ft_strlen(buf) - 1 : ft_strlen(buf);
	while (j < len / 2)
	{
		tmp = buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = tmp;
	}
	f_intzero = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

int				print_x(va_list *ap, t_flags *flags, char c)
{
	int			len;
	int			res;
	char		*number;

	res = 0;
	f_hex = 1;
	number = convert_x(ap, flags, c);
	f_sign += (number[0] == '-') ? 1 : 0;
	ignored_flag(flags);
	if (number[0] == '0' && (f_dot && !f_dot_l))
		return (print_sign(flags));
	len = f_hash ? ft_strlen(number) + 2 : ft_strlen(number);
	if (f_spaces_l && !f_minus)
		res += print_space(flags, len);
	res += (number[0] == '-') ? plus_minus(flags, -1, c) : plus_minus(flags, 1, c);
	if (f_zero)
		res += print_space(flags, len);
	res += print_dot(flags, len);
	if (number[0] == 0 && !(f_dot && !f_dot_l))
		res += ft_putchar('0');
	res += ft_putstr(number);
	if (f_spaces_l && f_minus)
		res += print_space(flags, len);
	free(number);
	return (res);
}

int				print_number(va_list *ap, t_flags *flags, char c)
{
	int			i;

	i = 0;
	if (c == 'd' || (c == 'i' && !f_ll))
		i += print_i(ap, flags);
	if (c == 'u')
		i += print_u(ap, flags);
	if (f_ll == 1)
		i += print_l(ap, flags);
	if (f_ll == 2)
		i += print_ll(ap, flags);
	if (c == 'x' || c == 'X')
		i += print_x(ap, flags, c);
	return (i);
}