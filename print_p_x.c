/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:04:52 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 11:04:56 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static char	*convert_llx(char buf[BSIZE], va_list *ap, t_flags *flags, char c)
{
	int					j;
	int					len;
	unsigned long long	n;

	j = 0;
	F_HEX = 1;
	F_HASH = (c == 'p') ? 1 : F_HASH;
	ft_bzero(buf, BSIZE);
	n = va_arg(*ap, unsigned long long);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 16 < 10) ? n % 16 + '0' : n % 16 - 10 + 'a';
		n /= 16;
	}
	len = ft_strlen(buf);
	while ((int)n < len / 2)
	{
		j = (int)buf[n];
		buf[n] = buf[len - n - 1];
		buf[len - 1 - n++] = (char)j;
	}
	F_INTZERO = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

static char	*convert_x(char buf[BSIZE], va_list *ap, t_flags *flags, char c)
{
	int					j;
	int					len;
	unsigned			n;

	j = 0;
	F_HEX = 1;
	ft_bzero(buf, BSIZE);
	n = va_arg(*ap, unsigned);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 16 < 10) ? n % 16 + '0' : n % 16 - 10 + 'a';
		n /= 16;
	}
	len = ft_strlen(buf);
	while ((int)n < len / 2)
	{
		j = (int)buf[n];
		buf[n] = buf[len - n - 1];
		buf[len - 1 - n++] = (char)j;
	}
	F_INTZERO = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

int			print_p(va_list *ap, t_flags *flags)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_llx(num, ap, flags, 'p');
	ignored_flags(flags);
	len = (F_INTZERO && F_DOT && !F_DOT_L) ? 2 : ft_strlen(num) + 2;
	if (F_INTZERO && F_DOT && F_DOT_L > F_SPACES_L)
		return (ft_putstr("0x") + print_dot(flags, 0));
	else if (F_INTZERO && F_ZERO_L && !F_DOT && !F_SPACES_L)
		return (ft_putstr("0x") + print_space_ch(F_ZERO_L - 2, '0'));
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	if (num[0] == '0' && (F_DOT && !F_DOT_L))
		return (ft_putstr("0x") + res);
	res += plus_minus(flags, 1, 'x');
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += (num[0] == '0') ? ft_putstr("0x0") : ft_putstr(num);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int			print_x(va_list *ap, t_flags *flags, char c)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_x(num, ap, flags, c);
	F_HEX = 1;
	ignored_flags(flags);
	if (num[0] == '0' && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = F_HASH ? ft_strlen(num) + 2 : ft_strlen(num);
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
	return (res);
}

int			print_llx(va_list *ap, t_flags *flags, char c)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_llx(num, ap, flags, c);
	ignored_flags(flags);
	if (num[0] == '0' && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = F_HASH ? ft_strlen(num) + 2 : ft_strlen(num);
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
	return (res);
}
