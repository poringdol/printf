/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 00:40:38 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/26 00:41:38 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static int	print_hash(t_flags *f)
{
	int n;

	n = 0;
	ignored_flags(f);
	if (f->spaces_l && !f->minus)
		n += print_space_num(f, 1);
	n += ft_putchar('0');
	if (f->zero)
		n += print_space_num(f, 1);
	n += print_dot(f, 1);
	if (f->spaces_l && f->minus)
		n += print_space_num(f, 1);
	return (n);
}

static char	*convert_llo(va_list *ap, t_flags *f)
{
	int					j;
	int					len;
	unsigned long long	n;
	char				*buf;

	j = 0;
	buf = (char *)ft_calloc(60, 1);
	n = va_arg(*ap, unsigned long long);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 8 < 10) ? n % 8 + '0' : n % 8 - 10 + 'a';
		n /= 8;
	}
	j = 0;
	len = ft_strlen(buf);
	while (j < len / 2)
	{
		n = (int)buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = (char)n;
	}
	f->intzero = (buf[0] == '0') ? 1 : 0;
	return (buf);
}

static char	*convert_o(va_list *ap, t_flags *f)
{
	int					j;
	int					len;
	unsigned			n;
	char				*buf;

	j = 0;
	buf = (char *)ft_calloc(60, 1);
	n = va_arg(*ap, unsigned);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 8 < 10) ? n % 8 + '0' : n % 8 - 10 + 'a';
		n /= 8;
	}
	j = 0;
	len = ft_strlen(buf);
	while (j < len / 2)
	{
		n = (int)buf[j];
		buf[j] = buf[len - j - 1];
		buf[len - 1 - j++] = (char)n;
	}
	f->intzero = (buf[0] == '0') ? 1 : 0;
	return (buf);
}

int			print_o(va_list *ap, t_flags *f, char c)
{
	int					len;
	int					res;
	char				*num;

	res = 0;
	f->oct = 1;
	num = convert_o(ap, f);
	if (f->hash && f->intzero && f->dot)
		return (print_hash(f));
	ignored_flags(f);
	if (f->intzero && f->dot && !f->dot_l && !f->hash)
		return (print_sign(f));
	len = f->hash ? ft_strlen(num) + 1 : ft_strlen(num);
	res += (f->spaces_l && !f->minus) ? print_space_num(f, len) : 0;
	res += plus_minus(f, 1, c);
	res += f->zero ? print_space_num(f, len) : 0;
	res += print_dot(f, len);
	if (f->intzero && f->dot && !f->dot_l)
		res += ft_putchar('0');
	res += ft_putstr(num);
	res += (f->spaces_l && f->minus) ? print_space_num(f, len) : 0;
	free(num);
	return (res);
}

int			print_llo(va_list *ap, t_flags *f, char c)
{
	int					len;
	int					res;
	char				*num;

	res = 0;
	f->oct = 1;
	num = convert_llo(ap, f);
	if (f->hash && f->intzero && f->dot)
		return (print_hash(f));
	ignored_flags(f);
	if (num[0] == '0' && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = f->hash ? ft_strlen(num) + 1 : ft_strlen(num);
	res += (f->spaces_l && !f->minus) ? print_space_num(f, len) : 0;
	res += plus_minus(f, 1, c);
	res += f->zero ? print_space_num(f, len) : 0;
	res += print_dot(f, len);
	if (num[0] == 0 && !(f->dot && !f->dot_l))
		res += ft_putchar('0');
	res += ft_putstr(num);
	res += (f->spaces_l && f->minus) ? print_space_num(f, len) : 0;
	free(num);
	return (res);
}
