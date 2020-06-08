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
#include <float.h>
#include "libftprintf.h"
#include "libft.h"

int				print_f(t_flags *f, double d)
{
	int			len;
	int			res;

	res = 0;
	f->sign += (d < 0) ? 1 : 0;
	len = len_fnumber(f, d) + f->dot_l +
	((f->plus || f->hidden || f->nzero) && !(d < 0) ? 1 : 0);
	len += (f->dot_l || f->hash) ? 1 : 0;
	len += ((f->dot && !f->dot_l) || f->dot_l) ? 0 : 6;
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, d, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += print_float(f, d);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_lf(va_list *ap, t_flags *f)
{
	long double	d;
	int			len;
	int			res;

	res = 0;
	f->sign += (d = va_arg(*ap, long double)) < 0 ? 1 : 0;
	len = len_fnumber(f, d) + f->dot_l +
	((f->plus || f->hidden) && !(d < 0) ? 1 : 0);
	len += (f->dot_l || f->hash) ? 1 : 0;
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, d, 0);
	res += (d == -LDBL_MIN) ? ft_putchar('-') : 0;
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += print_float(f, d);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_e(t_flags *f, double d)
{
	int			len;
	int			res;
	double		tmp;

	res = 0;
	tmp = d;
	f->sign += (d < 0) ? 1 : 0;
	len = 3 + (f->dot ? f->dot_l : 6) +
	((len_enumber(&tmp) > 99) ? 3 : 2) +
	((f->plus || f->hidden || d < 0) ? 1 : 0);
	len += (f->dot_l || f->hash) ? 1 : 0;
	if (f->g)
		len -= f->dot_l ? 2 : 0;
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, d, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += print_efloat(f, d);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_g(t_flags *f, double d)
{
	int			sign;
	int			exp;
	int			len;
	double		tmp;

	sign = (ft_fabs(d) < 1) ? -1 : 1;
	tmp = d;
	len = len_enumber(&tmp) + 1;
	exp = len * sign;
	if (f->dot && f->dot_l)
		f->dot_l = f->dot_l > 0 ? f->dot_l : 0;
	if (f->dot && !f->dot_l)
		f->dot_l = 1;
	if (!f->dot)
	{
		f->dot = 1;
		f->dot_l = 6 > 0 ? 6 : 0;
	}
	return (exp > f->dot_l || exp < -4 ? print_e(f, d) : print_f(f, d));
}

int				print_feg(va_list *ap, t_flags *f, int c)
{
	double		d;

	d = (double)va_arg(*ap, double);
	if (isinfnan(&d))
		return (print_infnan(f, &d));
	if (c == 'f')
		return (print_f(f, d));
	if (c == 'e')
	{
		f->e = 1;
		return (print_e(f, d));
	}
	if (c == 'g')
	{
		f->g = 1;
		return (print_g(f, d));
	}
	else
		return (0);
}
