/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:27:21 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 11:27:30 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"

int	print_number(va_list *ap, t_flags *f, char c)
{
	int					n;

	n = 0;
	if ((c == 'd' || c == 'i') && f->ll)
		n += print_lli(ap, f);
	else if ((c == 'd' || c == 'i') && f->hh)
		n += f->hh == 1 ? print_hi(ap, f) : print_hhi(ap, f);
	else if ((c == 'd' || c == 'i'))
		n += print_i(ap, f);
	else if (c == 'u' && f->ll)
		n += f->ll == 1 ? print_lu(ap, f) : print_llu(ap, f);
	else if (c == 'u')
		n += print_u(ap, f);
	else if ((c == 'x' || c == 'X') && f->ll)
		n += print_llx(ap, f, c);
	else if (c == 'x' || c == 'X')
		n += print_x(ap, f, c);
	else if ((c == 'o') && f->ll)
		n += print_llo(ap, f, c);
	else if (c == 'o')
		n += print_o(ap, f, c);
	else if (c == 'f' || c == 'F' || c == 'e' || c == 'g')
		n += print_feg(ap, f, c);
	return (n);
}

int	put_number(long long n)
{
	if (n == LLONG_MIN)
		return (ft_putstr("9223372036854775808"));
	if (n >= 0)
		return (ft_putnbr(n));
	else
		return (ft_putnbr(-n));
}

int	len_number(t_flags *f, long long n)
{
	long long			i;
	long long			tmp;
	int					len;

	len = f->sign ? 1 : 0;
	if (n == LLONG_MIN)
		return (20);
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (f->sign ? 20 : 19);
		i *= 10;
		len++;
	}
	return (n ? len : ++len);
}

int	len_unumber(unsigned long long n)
{
	int					len;
	unsigned long long	tmp;

	tmp = n;
	len = 0;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	return (n ? len : ++len);
}
