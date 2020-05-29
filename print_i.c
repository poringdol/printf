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

int				print_i(va_list *ap, t_flags *flags)
{
	int			n;
	int			len;
	int			res;

	res = 0;
	F_SIGN += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, n, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_lli(va_list *ap, t_flags *flags)
{
	long long			n;
	int					len;
	int					res;

	res = 0;
	F_SIGN += (n = va_arg(*ap, long long)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, n, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_hi(va_list *ap, t_flags *flags)
{
	short				n;
	int					len;
	int					res;

	res = 0;
	F_SIGN += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, n, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_hhi(va_list *ap, t_flags *flags)
{
	char				n;
	int					len;
	int					res;

	res = 0;
	F_SIGN += (n = va_arg(*ap, int)) < 0 ? 1 : 0;
	F_INTZERO = (n == 0) ? 1 : 0;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_number(flags, n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	res += plus_minus(flags, n, 0);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += put_number(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}
