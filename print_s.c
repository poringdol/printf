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

static int		ft_putnstr(char const *s, int n)
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

static int		print_null(t_flags *flags)
{
	int		spaces;
	int		len;

	len = ft_strlen("(null)");
	if (F_DOT && F_DOT_L < len)
		len = F_DOT_L;
	spaces = F_SPACES_L - len;
	if (F_SPACES_L)
	{
		return (F_MINUS ?
		(ft_putnstr("(null)", len) + print_space_ch(spaces, ' ')) :
		print_space_ch(spaces, ' ') + ft_putnstr("(null)", len));
	}
	return (ft_putnstr("(null)", len));
}

int				print_s(va_list *ap, t_flags *flags)
{
	int		n;
	int		len;
	int		spaces;
	char	*string;

	n = 0;
	if (!(string = va_arg(*ap, char *)))
		return (print_null(flags));
	ignored_flags(flags);
	n += print_space_ch(F_ZERO_L - ft_strlen(string), '0');
	len = ft_strlen(string);
	if (F_DOT)
		len = (F_DOT_L < len) ? F_DOT_L : len;
	spaces = F_SPACES_L - len;
	n += (F_MINUS ? (ft_putnstr(string, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(string, len));
	return (n);
}
