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

static int	ft_wch_strlen(const wchar_t *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] & 0x1FFF80) == 0)
			len += 1;
		else if ((str[i] & 0x1FF800) == 0)
			len += 2;
		else if ((str[i] & 0x10000) == 0)
			len += 3;
		else if (str[i] <= 0x10FFFF)
			len += 4;
		i++;
	}
	return (len);
}

int				print_lc(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	int		wch;
	char	ch[5];

	n = 0;
	wch = va_arg(*ap, int);
	ft_bzero(ch, 5);
	convert_wch_to_ch(ch, wch);
	len = ft_strlen(ch);
	ignored_flags(f);
	n = print_space_ch(f->zero_l - ft_strlen(ch), '0');
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (write(1, ch, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + write(1, ch, len));
	return (n);
}

int				print_ls(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	int		*string;
	char	*ch;

	n = 0;
	if (!(string = va_arg(*ap, int *)))
		return (print_null(f));
	ch = ft_calloc(ft_wch_strlen(string) + 1, 4);
	convert_wstr_to_str(ch, string);
	len = ft_strlen(ch);
	ignored_flags(f);
	n = print_space_ch(f->zero_l - ft_strlen(ch), '0');
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (write(1, ch, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + write(1, ch, len));
	free(ch);
	return (n);
}
