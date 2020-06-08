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

int			print_c(va_list *ap, t_flags *f)
{
	int spaces;
	int	n;
	int ch;

	n = 0;
	ch = va_arg(*ap, int);
	spaces = f->spaces_l - 1;
	n += print_space_ch(f->zero_l - 1, '0');
	n += f->minus ? (ft_putchar(ch) + print_space_ch(spaces, ' ')) :
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

int			nospec(t_flags *f, char c)
{
	int	res;

	res = 0;
	f->spaces_l = ft_isgraph(c) ? f->spaces_l - 1 : f->spaces_l;
	f->zero_l = ft_isgraph(c) ? f->zero_l - 1 : f->zero_l;
	if (f->spaces_l && !f->minus && f->spaces_l > f->zero_l)
		res += print_space_ch(f->spaces_l, ' ');
	if (f->zero_l > f->spaces_l)
		res += print_space_ch(f->zero_l, '0');
	res += ft_isgraph(c) ? ft_putchar(c) : 0;
	if (f->spaces_l && f->minus && f->spaces_l > f->zero_l)
		res += print_space_ch(f->spaces_l, ' ');
	return (res);
}
