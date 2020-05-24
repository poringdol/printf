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
	int			i;

	i = 0;
	if ((c == 'd' || c == 'i') && !F_LL && !F_HH)
		i += print_i(ap, flags);
	else if (c == 'u')
		i += print_u(ap, flags);
	else if ((c == 'd' || c == 'i') && F_LL)
		i += print_lli(ap, flags);
	else if ((c == 'd' || c == 'i') && F_HH)
		i += print_hhi(ap, flags);
	else if (F_LL && (c == 'x' || c == 'X'))
		i += print_x(ap, flags, c);
	else if (c == 'x' || c == 'X')
		i += print_x(ap, flags, c);
	return (i);
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
	long long	i;
	long long	tmp;
	int			len;

	len = !flags->sign ? 0 : 1;
	if (n == LLONG_MIN)
		return (19);
	tmp = n > 0 ? n : -n;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (19);
		i *= 10;
		len++;
	}
	return (n ? len : ++len);
}
