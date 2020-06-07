/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f_e_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:04:55 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 00:46:09 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int				print_f(t_flags *flags, double d)
{
	int			len;
	int			res;

	res = 0;
	F_SIGN += (d < 0) ? 1 : 0;
	len = len_fnumber(flags, d) + F_DOT_L +
	((F_PLUS || F_HIDDEN || F_NZERO) && !(d < 0) ? 1 : 0);
	len += (F_DOT_L || F_HASH) ? 1 : 0;
	len += ((F_DOT && !F_DOT_L) || F_DOT_L) ? 0 : 6;
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, d, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += print_float(flags, d);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_lf(va_list *ap, t_flags *flags)
{
	long double	d;
	int			len;
	int			res;

	res = 0;
	F_SIGN += (d = va_arg(*ap, long double)) < 0 ? 1 : 0;
	len = len_fnumber(flags, d) + F_DOT_L +
	((F_PLUS || F_HIDDEN) && !(d < 0) ? 1 : 0);
	len += (F_DOT_L || F_HASH) ? 1 : 0;
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, d, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += print_float(flags, d);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_e(t_flags *flags, double d)
{
	int			len;
	int			res;
	double		tmp;

	res = 0;
	tmp = d;
	F_SIGN += (d < 0) ? 1 : 0;
	len = 3 + (F_DOT ? F_DOT_L : 6) +
	((len_enumber(&tmp) > 99) ? 3 : 2) +
	((F_PLUS || F_HIDDEN || d < 0) ? 1 : 0);
	len += (F_DOT_L || F_HASH) ? 1 : 0;
	if (flags->g)
		len -= F_DOT_L ? 2 : 0;
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, d, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += print_efloat(flags, d);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_g(t_flags *flags, double d)
{
	int			sign;
	int			exp;
	int			len;
	double		tmp;

	sign = (ft_fabs(d) < 1) ? -1 : 1;
	tmp = d;
	len = len_enumber(&tmp) + 1;
	exp = len * sign;
	if (F_DOT && F_DOT_L)
		F_DOT_L = F_DOT_L > 0 ? F_DOT_L : 0;
	if (F_DOT && !F_DOT_L)
		F_DOT_L = 1;
	if (!F_DOT)
	{
		F_DOT = 1;
		F_DOT_L = 6 > 0 ? 6 : 0;
	}
	return (exp > F_DOT_L || exp < -4 ? print_e(flags, d) : print_f(flags, d));
}

int				print_feg(va_list *ap, t_flags *flags, int c)
{
	double		d;

	d = (double)va_arg(*ap, double);
	if (isinfnan(&d))
		return (print_infnan(flags, &d));
	if (c == 'f')
		return (print_f(flags, d));
	if (c == 'e')
	{
		flags->e = 1;
		return (print_e(flags, d));
	}
	if (c == 'g')
	{
		flags->g = 1;
		return (print_g(flags, d));
	}
	else
		return (0);
}
