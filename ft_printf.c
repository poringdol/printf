/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:15:43 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 10:15:47 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list ap;
	t_flags	*f;
	int		flag;
	int		n;

	va_start(ap, format);
	n = 0;
	flag = 0;
	f = create_flags();
	while (*format)
	{
		if (*format == '%' && !flag)
			flag = 1;
		else if (*format != '%' && !flag)
			n += write(1, format, 1);
		else if (flag)
		{
			n = check_params((char **)&format, &ap, f, n);
			flag = 0;
		}
		format += *format ? 1 : 0;
	}
	free(f);
	va_end(ap);
	return (n);
}
