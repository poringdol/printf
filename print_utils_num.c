/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:32:11 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 11:32:14 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

int	print_space_num(t_flags *flags, int len)
{
	int	i;
	int	space;

	i = 0;
	if (F_SPACES_L > F_DOT_L)
	{
		space = F_SPACES_L - ((F_DOT_L > len) ? F_DOT_L : len);
		space -= (F_SIGN && F_DOT && F_DOT_L >= len) ? 1 : 0;
		while (i < space)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (F_ZERO_L > F_DOT_L)
	{
		space = F_ZERO_L - (F_DOT_L ? F_DOT_L : len);
		while (i < F_ZERO_L - F_DOT_L - len)
		{
			ft_putchar('0');
			i++;
		}
	}
	return (i);
}

int	plus_minus(t_flags *flags, long long n, int c)
{
	if (!n && !(F_ZERO_L) && ((F_DOT && !(F_DOT_L)) ||
	(F_MINUS && !(F_SPACES_L)) || (F_PLUS && !(F_SPACES_L))))
		return (0);
	if (F_PLUS && n >= 0)
		return (ft_putchar('+'));
	if (F_HIDDEN && n >= 0)
		return (ft_putchar(' '));
	if (n < 0)
		return (ft_putchar('-'));
	if (F_HASH && F_HEX)
		return (c == 'x' ? ft_putstr("0x") : ft_putstr("0X"));
	if (F_HASH && F_OCT)
		return (ft_putchar('0'));
	return (0);
}

int	print_dot(t_flags *flags, int len)
{
	int	i;
	int	dot;

	i = 0;
	dot = F_DOT_L - len;
	if (F_SIGN)
		dot++;
	while (i < dot)
	{
		ft_putchar('0');
		i++;
	}
	return (i);
}

int	print_sign(t_flags *flags)
{
	int	len;
	int	res;

	if (!F_SPACES_L && !F_ZERO_L && !F_PLUS && !F_HIDDEN)
		return (0);
	res = 0;
	len = F_SIGN ? 1 : 0;
	F_SPACES_L -= (F_SIGN ? 0 : 1);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += F_PLUS ? ft_putchar('+') : ft_putchar(' ');
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int	print_percent(t_flags *flags)
{
	int	res;

	res = 0;
	// ignored_flags(flags);
	F_DOT = 0;
	F_DOT_L = 0;
	if ((F_SPACES_L && !F_MINUS) || F_ZERO_L)
		res += print_space_num(flags, 1);
	res += ft_putchar('%');
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, 1);
	return (res);
}
