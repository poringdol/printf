#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static void		getfnbr(unsigned long long d, char buf[48])
{
	int			len;

	len = len_unumber(d) - 1;
	buf[len] = '\0';
	while (d != 1)
	{
		buf[len - 1] = d % 10 + '0';
		d /= 10;
		len--;
	}
}

static int		print_float(t_flags *flags, double f)
{
	int			n;
	int			accur;
	char		buf[48];
	long long	ll;

	accur = F_DOT ? F_DOT_L : 6;
	n = ft_putnbr((long long)f) + (accur > 0 ? ft_putchar('.') : 0);
	ll = (long long)f;
	f = (f -ll + 1) * ft_pow(10, accur + 1);
	f = ((long)f % 10 > 4) ? f / 10 + 1 : f / 10;
	getfnbr(f, buf);
	n += ft_putstr(buf);
	return (n);
}

static int		put_fnumber(t_flags *flags, double f)
{
	if (f >= 0)
		return (print_float(flags, f));
	else
		return (print_float(flags, -f));
}

int			print_f(va_list *ap, t_flags *flags)
{
	double		n;
	int			len;
	int			res;

	res = 0;
	n = va_arg(*ap, double);
	// F_SIGN += (n = va_arg(*ap, double)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_number(flags, n) + F_DOT_L;
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, n, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += put_fnumber(flags, n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}