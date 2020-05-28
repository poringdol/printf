/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 16:14:08 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/28 16:14:11 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int				print_u(va_list *ap, t_flags *flags)
{
	unsigned			n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned);
	F_UNSIGN = 1;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_unumber(n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += ft_putunbr(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_lu(va_list *ap, t_flags *flags)
{
	unsigned long		n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned long);
	F_UNSIGN = 1;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_unumber(n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += ft_putunbr(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}

int				print_llu(va_list *ap, t_flags *flags)
{
	unsigned long long	n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned long long);
	F_UNSIGN = 1;
	ignored_flags(flags);
	if (!n && (F_DOT && !F_DOT_L))
		return (print_sign(flags));
	len = len_unumber(n);
	if (F_SPACES_L && !F_MINUS)
		res += print_space_num(flags, len);
	if (F_ZERO)
		res += print_space_num(flags, len);
	res += print_dot(flags, len);
	res += ft_putunbr(n);
	if (F_SPACES_L && F_MINUS)
		res += print_space_num(flags, len);
	return (res);
}
