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

int				print_u(va_list *ap, t_flags *f)
{
	unsigned			n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned);
	f->unsign = 1;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_unumber(n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += ft_putunbr(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_lu(va_list *ap, t_flags *f)
{
	unsigned long		n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned long);
	f->unsign = 1;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_unumber(n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += ft_putunbr(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int				print_llu(va_list *ap, t_flags *f)
{
	unsigned long long	n;
	int					len;
	int					res;

	res = 0;
	n = va_arg(*ap, unsigned long long);
	f->unsign = 1;
	ignored_flags(f);
	if (!n && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = len_unumber(n);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += ft_putunbr(n);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}
