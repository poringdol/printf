#include <stdarg.h>
#include <float.h>
#include "libftprintf.h"
#include "libft.h"

static int	len_fnumber(t_flags *flags, double n)
{
	double				i;
	double				tmp;
	int					len;

	len = !flags->sign ? 0 : 1;
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (++len);
		i *= 10;
		len++;
	}
	return (n ? len : ++len);
}

static void		getfnbr(unsigned long long d, char buf[48])
{
	int			len;

	buf[0] = '\0';
	len = len_unumber(d) - 1;
	if (len <= 0)
		return ;
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
	double		tmp;

	accur = F_DOT ? F_DOT_L : 6;
	tmp = f;
	tmp = f / ft_pow(10, len_fnumber(flags, f));
	if (F_DOT && !F_DOT_L)
		f += tmp > 4 ? 1 : 0;
	n = ft_putnbr((long long)f) + (accur > 0 ? ft_putchar('.') : 0);
	f = (f - (long long)f + 1) * ft_pow(10, accur + 1);
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
	F_SIGN += (n = va_arg(*ap, double)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	if (n == 0 && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_fnumber(flags, n) + F_DOT_L + ((F_DOT && !F_DOT_L) ? 0 : 1);
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