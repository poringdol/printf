/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:32:11 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 00:47:24 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

int	print_space_num(t_flags *f, int len)
{
	int	i;
	int	space;

	i = 0;
	if (f->spaces_l > f->dot_l)
	{
		space = f->spaces_l - ((f->dot_l > len) ? f->dot_l : len);
		space -= (!f->unsign && f->sign && f->dot && f->dot_l >= len) ? 1 : 0;
		while (i < space)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (f->zero_l > f->dot_l)
	{
		space = f->zero_l - (f->dot_l > len ? f->dot_l : len);
		while (i < space)
		{
			ft_putchar('0');
			i++;
		}
	}
	return (i);
}

int	plus_minus(t_flags *f, double n, int c)
{
	if (!n && !(f->zero_l) && ((f->dot && !(f->dot_l))))
		return (0);
	if (f->plus && n >= 0)
		return (ft_putchar('+'));
	if (f->hidden && n >= 0)
		return (ft_putchar(' '));
	if (n < 0 || f->nzero)
		return (ft_putchar('-'));
	if (f->hash && f->hex)
		return (c == 'x' ? ft_putstr("0x") : ft_putstr("0X"));
	if (f->hash && f->oct)
		return (ft_putchar('0'));
	return (0);
}

int	print_dot(t_flags *f, int len)
{
	int	i;
	int	dot;

	i = 0;
	dot = f->dot_l - len;
	if (f->sign && !f->unsign)
		dot++;
	while (i < dot)
	{
		ft_putchar('0');
		i++;
	}
	return (i);
}

int	print_sign(t_flags *f)
{
	int	len;
	int	n;

	if (!f->spaces_l && !f->zero_l && !f->plus && !f->hidden)
		return (0);
	n = 0;
	len = f->sign && !f->unsign ? 1 : 0;
	f->spaces_l -= (f->sign || f->unsign) ? 0 : 1;
	if (f->spaces_l && !f->minus)
		n += print_space_num(f, len);
	if ((f->unsign && f->dot_l) || !f->unsign)
		n += f->plus ? ft_putchar('+') : ft_putchar(' ');
	if (f->zero)
		n += print_space_num(f, len);
	n += print_dot(f, len);
	if (f->spaces_l && f->minus)
		n += print_space_num(f, len);
	return (n);
}

int	print_percent(t_flags *f)
{
	int	n;

	n = 0;
	f->dot = 0;
	f->dot_l = 0;
	ignored_flags(f);
	if ((f->spaces_l && !f->minus) || f->zero_l)
		n += print_space_num(f, 1);
	n += ft_putchar('%');
	if (f->spaces_l && f->minus)
		n += print_space_num(f, 1);
	return (n);
}
