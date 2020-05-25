/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:33:18 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 10:33:32 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "libftprintf.h"

int			print_c(va_list *ap, t_flags *flags)
{
	int spaces;
	int	n;
	int ch;

	n = 0;
	ch = va_arg(*ap, int);
	spaces = flags->spaces_len - 1;
	n += print_space_ch(F_ZERO_L - 1, '0');
	n += flags->minus ? (ft_putchar(ch) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putchar(ch);
	return (n);
}

int			print_space_ch(int n, int c)
{
	int i;

	i = 0;
	while (i++ < n)
		ft_putchar(c);
	return (n > 0 ? n : 0);
}
