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

static char	*convert_llx(char buf[BSIZE], va_list *ap, t_flags *f, char c)
{
	int					j;
	int					len;
	unsigned long long	n;

	j = 0;
	f->hex = 1;
	f->hash = (c == 'p') ? 1 : f->hash;
	ft_bzero(buf, BSIZE);
	n = va_arg(*ap, unsigned long long);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 16 < 10) ? n % 16 + '0' : n % 16 - 10 + 'a';
		n /= 16;
	}
	len = ft_strlen(buf);
	while ((int)n < len / 2)
	{
		j = (int)buf[n];
		buf[n] = buf[len - n - 1];
		buf[len - 1 - n++] = (char)j;
	}
	f->intzero = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

static char	*convert_x(char buf[BSIZE], va_list *ap, t_flags *f, char c)
{
	int					j;
	int					len;
	unsigned			n;

	j = 0;
	f->hex = 1;
	ft_bzero(buf, BSIZE);
	n = va_arg(*ap, unsigned);
	buf[0] += (n == 0) ? '0' : 0;
	while (n)
	{
		buf[j++] = (n % 16 < 10) ? n % 16 + '0' : n % 16 - 10 + 'a';
		n /= 16;
	}
	len = ft_strlen(buf);
	while ((int)n < len / 2)
	{
		j = (int)buf[n];
		buf[n] = buf[len - n - 1];
		buf[len - 1 - n++] = (char)j;
	}
	f->intzero = (buf[0] == '0') ? 1 : 0;
	return ((c == 'X') ? ft_strupcase(buf) : buf);
}

int			print_p(va_list *ap, t_flags *f)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_llx(num, ap, f, 'p');
	ignored_flags(f);
	len = (f->intzero && f->dot && !f->dot_l) ? 2 : ft_strlen(num) + 2;
	if (f->intzero && f->dot && f->dot_l > f->spaces_l)
		return (ft_putstr("0x") + print_dot(f, 0));
	else if (f->intzero && f->zero_l && !f->dot && !f->spaces_l)
		return (ft_putstr("0x") + print_space_ch(f->zero_l - 2, '0'));
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	if (num[0] == '0' && (f->dot && !f->dot_l))
		return (ft_putstr("0x") + res);
	res += plus_minus(f, 1, 'x');
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	res += (num[0] == '0') ? ft_putstr("0x0") : ft_putstr(num);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int			print_x(va_list *ap, t_flags *f, char c)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_x(num, ap, f, c);
	f->hex = 1;
	ignored_flags(f);
	if (num[0] == '0' && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = f->hash ? ft_strlen(num) + 2 : ft_strlen(num);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, 1, c);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	if (num[0] == 0 && !(f->dot && !f->dot_l))
		res += ft_putchar('0');
	res += ft_putstr(num);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}

int			print_llx(va_list *ap, t_flags *f, char c)
{
	int					len;
	int					res;
	char				num[BSIZE];

	res = 0;
	convert_llx(num, ap, f, c);
	ignored_flags(f);
	if (num[0] == '0' && (f->dot && !f->dot_l))
		return (print_sign(f));
	len = f->hash ? ft_strlen(num) + 2 : ft_strlen(num);
	if (f->spaces_l && !f->minus)
		res += print_space_num(f, len);
	res += plus_minus(f, 1, c);
	if (f->zero)
		res += print_space_num(f, len);
	res += print_dot(f, len);
	if (num[0] == 0 && !(f->dot && !f->dot_l))
		res += ft_putchar('0');
	res += ft_putstr(num);
	if (f->spaces_l && f->minus)
		res += print_space_num(f, len);
	return (res);
}
