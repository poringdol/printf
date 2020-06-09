/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lc_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 09:25:49 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/09 09:25:52 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static size_t	ft_wch_strlen(const wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				print_lc(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	wchar_t	wch;
	char	ch[5];

	n = 0;
	wch = va_arg(*ap, wchar_t);
	ft_bzero(ch, 5);
	convert_wch_to_ch(ch, wch);
	len = ft_strlen(ch);
	ignored_flags(f);
	n = print_space_ch(f->zero_l - ft_strlen(ch), '0');
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (ft_putnstr(ch, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(ch, len));
	return (n);
}

int				print_ls(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	wchar_t	*string;
	char	*ch;

	n = 0;
	if (!(string = va_arg(*ap, wchar_t *)))
		return (print_null(f));
	ch = ft_calloc(ft_wch_strlen(string), 4);
	convert_wstr_to_str(ch, string);
	len = ft_strlen(ch);
	ignored_flags(f);
	n = print_space_ch(f->zero_l - ft_strlen(ch), '0');
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (ft_putnstr(ch, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(ch, len));
	free(ch);
	return (n);
}
