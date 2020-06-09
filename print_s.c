/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:33:36 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 10:33:41 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int	print_null(t_flags *f)
{
	int		spaces;
	int		len;

	len = ft_strlen("(null)");
	if (f->dot && f->dot_l < len)
		len = f->dot_l;
	spaces = f->spaces_l - len;
	if (f->spaces_l)
	{
		return (f->minus ?
		(write(1, "(null)", len) + print_space_ch(spaces, ' ')) :
		print_space_ch(spaces, ' ') + write(1, "(null)", len));
	}
	return (write(1, "(null)", len));
}

int	print_s(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	char	*string;

	n = 0;
	if (!(string = va_arg(*ap, char *)))
		return (print_null(f));
	ignored_flags(f);
	n += print_space_ch(f->zero_l - ft_strlen(string), '0');
	len = ft_strlen(string);
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (write(1, string, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + write(1, string, len));
	return (n);
}
