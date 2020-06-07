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

int	print_number(va_list *ap, t_flags *flags, char c)
{
	int					n;

	n = 0;
	if ((c == 'd' || c == 'i') && F_LL)
		n += print_lli(ap, flags);
	else if ((c == 'd' || c == 'i') && F_HH)
		n += F_HH == 1 ? print_hi(ap, flags) : print_hhi(ap, flags);
	else if ((c == 'd' || c == 'i'))
		n += print_i(ap, flags);
	else if (c == 'u' && F_LL)
		n += F_LL == 1 ? print_lu(ap, flags) : print_llu(ap, flags);
	else if (c == 'u')
		n += print_u(ap, flags);
	else if ((c == 'x' || c == 'X') && F_LL)
		n += print_llx(ap, flags, c);
	else if (c == 'x' || c == 'X')
		n += print_x(ap, flags, c);
	else if ((c == 'o') && F_LL)
		n += print_llo(ap, flags, c);
	else if (c == 'o')
		n += print_o(ap, flags, c);
	else if (c == 'f' || c == 'F' || c == 'e' || c == 'g')
		n += print_feg(ap, flags, c);
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

int	len_number(t_flags *flags, long long n)
{
	long long			i;
	long long			tmp;
	int					len;

	len = flags->sign ? 1 : 0;
	if (n == LLONG_MIN)
		return (20);
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (flags->sign ? 20 : 19);
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
