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

int				ft_putnstr(char const *s, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if (write(1, &s[i], 1))
			i++;
	}
	return (n);
}

int			print_null(t_flags *f)
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
		(ft_putnstr("(null)", len) + print_space_ch(spaces, ' ')) :
		print_space_ch(spaces, ' ') + ft_putnstr("(null)", len));
	}
	return (ft_putnstr("(null)", len));
}

int				print_s(va_list *ap, t_flags *f)
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
	n += (f->minus ? (ft_putnstr(string, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(string, len));
	return (n);
}
