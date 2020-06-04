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
	len = 4 + F_DOT_L +
	((len_enumber(&tmp) > 99) ? 3 : 2) +
	((F_PLUS || F_HIDDEN) && !(d < 0) ? 1 : 0);
	len += (F_DOT_L || F_HASH) ? 1 : 0;
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
	int			len_f;
	int			len_e;
	double		tmp;

	len_f = len_fnumber(flags, d) + F_DOT_L +
	((F_PLUS || F_HIDDEN) && !(d < 0) ? 1 : 0);
	len_f += (F_DOT_L || F_HASH) ? 1 : 0;
	len_e = 4 + F_DOT_L +
	((len_enumber(&tmp) > 99) ? 3 : 2) +
	((F_PLUS || F_HIDDEN) && !(d < 0) ? 1 : 0);
	return (len_f < len_e ? print_f(flags, d) : print_e(flags, d));
}

int				print_feg(va_list *ap, t_flags *flags, int c)
{
	double		d;

	d = (double)va_arg(*ap, double);
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
