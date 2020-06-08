/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:24:39 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/04 22:23:49 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int	check_params(char **str, va_list *ap, t_flags *f, int n)
{
	reset_flags(f);
	while (!isspecs(**str) && isflags(**str))
		set_flags(ap, f, str);
	ifnegative(f);
	if (**str == '%')
		return (n += print_percent(f));
	if (**str == 'c')
		n += print_c(ap, f);
	else if (**str == 's')
		n += print_s(ap, f);
	else if (**str == 'i' || **str == 'd' || **str == 'u' || **str == 'f' ||
	**str == 'F' || **str == 'x' || **str == 'X' || **str == 'o' ||
	**str == 'e' || **str == 'g')
		n += print_number(ap, f, **str);
	else if (**str == 'l' || **str == 'h' || **str == 'L')
		n += islongshort(ap, f, str);
	else if (**str == 'p')
		n += print_p(ap, f);
	else if (**str == 'n')
		*(va_arg(*ap, int *)) = n;
	else if (f->spaces_l || f->dot_l || f->zero_l)
		n += nospec(f, **str);
	else
		n += ft_putchar(**str);
	return (n);
}
