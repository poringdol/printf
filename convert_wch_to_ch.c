/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_wch_to_ch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 09:26:01 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/09 09:26:06 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static void	two_octet(char *convert, wchar_t wch, int *i)
{
	convert[(*i)++] |= 0xc0 | ((wch >> 6));
	convert[(*i)++] |= 0x80 | ((wch & 0x3f));
}

static void	three_octet(char *convert, wchar_t wch, int *i)
{
	convert[(*i)++] |= 0xe0 | ((wch >> 12));
	convert[(*i)++] |= 0x80 | ((wch >> 6 & 0x3f));
	convert[(*i)++] |= 0x80 | ((wch & 0x3f));
}

static void	four_octet(char *convert, wchar_t wch, int *i)
{
	convert[(*i)++] |= 0xf0 | (wch >> 18);
	convert[(*i)++] |= 0x80 | (wch >> 12 & 0x3f);
	convert[(*i)++] |= 0x80 | (wch >> 6 & 0x3f);
	convert[(*i)++] |= 0x80 | (wch & 0x3f);
}

/*
** 1 octet wch >= 0    && wch <= 127
** 2 octet wch >= 128  && wch <= 2047
** 3 octet wch >= 2048 && wch <= 65535
** 4 octet wch >= 65536 && wch <= 1114111
*/

void		convert_wstr_to_str(char *convert, wchar_t *wch)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (wch[j])
	{
		if ((wch[j] & 0x1FFF80) == 0)
			convert[i++] = wch[j];
		else if ((wch[j] & 0x1FF800) == 0)
			two_octet(convert, wch[j], &i);
		else if ((wch[j] & 0x10000) == 0)
			three_octet(convert, wch[j], &i);
		else if (wch[j] <= 0x10FFFF)
			four_octet(convert, wch[j], &i);
		j++;
	}
}

void		convert_wch_to_ch(char *convert, wchar_t wch)
{
	int		i;

	i = 0;
	if ((wch & 0x1FFF80) == 0)
		convert[i++] = wch;
	else if ((wch & 0x1FF800) == 0)
		two_octet(convert, wch, &i);
	else if ((wch & 0x10000) == 0)
		three_octet(convert, wch, &i);
	else if (wch <= 0x10FFFF)
		four_octet(convert, wch, &i);
}
