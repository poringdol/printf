#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static char	*convert_llo(va_list *ap, t_flags *flags)
{
	int					j;
	int					len;
	unsigned long long	n;
	char				*buf;

	j = 0;
	buf = (char *)ft_calloc(60, 1);
	n = va_arg(*ap, unsigned long long);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 8 < 10) ? n % 8 + '0' : n % 8 - 10 + 'a';
		n /= 8;
	}
	j = 0;
	len = ft_strlen(buf);
	while (j < len / 2)
	{
		n = (int)buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = (char)n;
	}
	F_INTZERO = (buf[0] == '0') ? 1 : 0;
	return (buf);
}

static char	*convert_o(va_list *ap, t_flags *flags)
{
	int					j;
	int					len;
	unsigned        	n;
	char				*buf;

	j = 0;
	buf = (char *)ft_calloc(60, 1);
	n = va_arg(*ap, unsigned);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 8 < 10) ? n % 8 + '0' : n % 8 - 10 + 'a';
		n /= 8;
	}
	j = 0;
	len = ft_strlen(buf);
	while (j < len / 2)
	{
		n = (int)buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = (char)n;
	}
	F_INTZERO = (buf[0] == '0') ? 1 : 0;
	return (buf);
}

int			print_o(va_list *ap, t_flags *flags, char c)
{
	int					len;
	int					res;
	char				*num;

	res = 0;
	F_OCT = 1;
	num = convert_o(ap, flags);
	ignored_flags(flags);
	if (num[0] == '0' && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = F_HASH ? ft_strlen(num) + 1 : ft_strlen(num);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, 1, c);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	if (num[0] == 0 && !(F_DOT && !F_DOT_L))
		res += ft_putchar('0');
	res += ft_putstr(num);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	free(num);
	return (res);
}

int			print_llo(va_list *ap, t_flags *flags, char c)
{
	int					len;
	int					res;
	char				*num;

	res = 0;
	F_OCT = 1;
	num = convert_llo(ap, flags);
	ignored_flags(flags);
	if (num[0] == '0' && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = F_HASH ? ft_strlen(num) + 1 : ft_strlen(num);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, 1, c);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	if (num[0] == 0 && !(F_DOT && !F_DOT_L))
		res += ft_putchar('0');
	res += ft_putstr(num);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	free(num);
	return (res);
}