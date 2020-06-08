/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_i_u_l_h.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:56:28 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 10:56:29 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int				print_i(va_list *ap, t_flags *f)
{
	int			n;
	int			len;
	int			res;

	res = 0;
	f->sign += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	f->intzero = (n == 0) ? 1 : 0;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_number(f, n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, n, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += put_number(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_lli(va_list *ap, t_flags *f)
{
	long long			n;
	int					len;
	int					res;

	res = 0;
	f->sign += (n = va_arg(*ap, long long)) < 0 ? 1 : 0;
	f->intzero = (n == 0) ? 1 : 0;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_number(f, n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, n, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += put_number(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_hi(va_list *ap, t_flags *f)
{
	short				n;
	int					len;
	int					res;

	res = 0;
	f->sign += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	f->intzero = (n == 0) ? 1 : 0;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_number(f, n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, n, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += put_number(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_hhi(va_list *ap, t_flags *f)
{
	char				n;
	int					len;
	int					res;

	res = 0;
	f->sign += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	f->intzero = (n == 0) ? 1 : 0;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_number(f, n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, n, 0);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += put_number(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}
