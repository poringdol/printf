/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 00:50:57 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 00:52:37 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include <string.h>
#include "libft.h"

static void		ft_itoa_e(int n, char buf[D_SIZE])
{
	unsigned int	len;
	unsigned int	tmp;

	ft_bzero(buf, D_SIZE);
	if (!n)
	{
		ft_strcpy(buf, "00");
		return ;
	}
	tmp = n;
	len = (n < 10) ? 2 : 1;
	buf[0] = (n < 10) ? '0' : 0;
	while ((n /= 10))
		len++;
	len--;
	while (tmp)
	{
		buf[len--] = tmp % 10 + '0';
		tmp /= 10;
	}
	return ;
}

int				len_fnumber(t_flags *flags, double d)
{
	double			i;
	double			tmp;
	int				len;

	len = !flags->sign ? 0 : 1;
	tmp = d > 0 ? d : -d;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (++len);
		i *= 10;
		len++;
	}
	return (d ? len : ++len);
}

int				len_enumber(double *d)
{
	int				len;

	*d = (*d < 0) ? -*d : *d;
	len = 0;
	while (*d < 1 && *d != 0)
	{
		*d *= 10;
		len++;
	}
	while (*d > 10)
	{
		*d /= 10;
		len++;
	}
	return (len);
}

int				print_efloat(t_flags *flags, double d)
{
	int				accuracy;
	int				len_e;
	char			sign[2];
	char			buf_i[D_SIZE];
	char			buf_f[D_SIZE];

	ft_bzero(sign, 2);
	ft_bzero(buf_i, D_SIZE);
	ft_bzero(buf_f, D_SIZE);
	(d < 1) ? ft_strcat(sign, "-") : ft_strcat(sign, "+");
	d = (d >= 0) ? d : -d;
	len_e = len_enumber(&d);
	accuracy = F_DOT ? F_DOT_L : 6;
	buf_float(d, buf_f, accuracy, flags);
	buf_integer(d, buf_i, accuracy, flags);
	ft_strcat(buf_i, ".");
	ft_strcat(buf_i, buf_f);
	float_params(buf_i, flags);
	ft_strcat(buf_i, "e");
	ft_strcat(buf_i, sign);
	ft_itoa_e(len_e, buf_f);
	ft_strcat(buf_i, buf_f);
	return (ft_putstr(buf_i));
}
