/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:24:39 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 11:24:42 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int	check_params(char **str, va_list *ap, t_flags *flags, int n)
{
	reset_flags(flags);
	while (!isspecs(**str) && isflags(**str))
		set_flags(ap, flags, str);
	ifnegative(flags);
	if (**str == '%')
		return (n += print_percent(flags));
	if (**str == 'c')
		n += print_c(ap, flags);
	else if (**str == 's')
		n += print_s(ap, flags);
	else if (**str == 'i' || **str == 'd' || **str == 'u' || **str == 'f')
		n += print_number(ap, flags, **str);
	else if (**str == 'x' || **str == 'X' || **str == 'o')
		n += print_number(ap, flags, **str);
	else if (**str == 'l' || **str == 'h')
		n += islongshort(ap, flags, str);
	else if (**str == 'p')
		n += print_p(ap, flags);
	else if (**str == 'n')
		*(va_arg(*ap, int *)) = n;
	else if (F_SPACES_L || F_DOT_L || F_ZERO_L)
		n += nospec(flags, **str);
	else
		n += ft_putchar(**str);
	return (n);
}
