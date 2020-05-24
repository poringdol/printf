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

static char	*convert_x(va_list *ap, t_flags *flags, char c)
{
	int			j;
	int			len;
	long long	n;
	char		*buf;

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
	len = (buf[0] == '-') ? ft_strlen(buf) - 1 : ft_strlen(buf);
	while (j < len / 2)
	{
		n = (int)buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = (char)n;
	}
	F_INTZERO = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

int			print_p(va_list *ap, t_flags *flags)
{
	int			len;
	int			res;
	char		*number;

	res = 0;
	F_HEX = 1;
	F_HASH = 1;
	number = convert_x(ap, flags, 'x');
	ignored_flags(flags);
	len = (number[0] == '0' && F_DOT && !F_DOL_L) ? 2 : ft_strlen(number) + 2;
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	if (number[0] == '0' && (F_DOT && !F_DOL_L))
		return (ft_putstr("0x") + res);
	res += plus_minus(flags, 1, 'x');
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += (number[0] == '0') ? ft_putstr("0x0") : ft_putstr(number);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	free(number);
	return (res);
}

int			print_x(va_list *ap, t_flags *flags, char c)
{
	int			len;
	int			res;
	char		*num;

	res = 0;
	F_HEX = 1;
	num = convert_x(ap, flags, c);
	F_SIGN += (num[0] == '-') ? 1 : 0;
	ignored_flags(flags);
	if (num[0] == '0' && (F_DOT && !F_DOL_L))
		return (print_sign(flags));
	len = F_HASH ? ft_strlen(num) + 2 : ft_strlen(num);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += (num[0] == '-') ? plus_minus(flags, -1, c) : plus_minus(flags, 1, c);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	if (num[0] == 0 && !(F_DOT && !F_DOL_L))
		res += ft_putchar('0');
	res += ft_putstr(num);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	free(num);
	return (res);
}
