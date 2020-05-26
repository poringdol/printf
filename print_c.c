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

int			nospec(t_flags *flags, char c)
{
	int	res;

	res = 0;
	F_SPACES_L = ft_isgraph(c) ? F_SPACES_L - 1 : F_SPACES_L;
	F_ZERO_L = ft_isgraph(c) ? F_ZERO_L - 1 : F_ZERO_L;
	if (F_SPACES_L && !F_MINUS && F_SPACES_L > F_ZERO_L)
		res += print_space_ch(F_SPACES_L, ' ');
	if (F_ZERO_L > F_SPACES_L)
		res += print_space_ch(F_ZERO_L, '0');;
	res += ft_isgraph(c) ? ft_putchar(c) : 0;
	if (F_SPACES_L && F_MINUS && F_SPACES_L > F_ZERO_L)
		res += print_space_ch(F_SPACES_L, ' ');
	return (res);
}
