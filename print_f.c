#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static int	print_float(t_flags *flags, float f)
{
	int			n;
	int			accur;
	long long	ll;

	accur = F_DOT ? F_DOT_L : 6;
	n = ft_putnbr((long long)f) + ft_putchar('.');
	ll = (long long)f;
	f -= (double)ll;
	while (accur)
	{
		f *= 10;
		accur--;
	}
	n += ft_putnbr((long long)f);
	return (n);
}

static int	put_fnumber(t_flags *flags, float n)
{
	if (n >= 0)
		return (print_float(flags, n));
	else
		return (print_float(flags, -n));
}

int			print_f(va_list *ap, t_flags *flags)
{
	double		n;
	int			len;
	int			res;

	res = 0;
	F_SIGN += (n = va_arg(*ap, double)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	float nn=-3.85;
	n=nn;
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