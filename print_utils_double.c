/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 00:47:39 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 01:44:23 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <limits.h>
#include "libftprintf.h"
#include "libft.h"

int		print_float(t_flags *f, double d)
{
	int			accuracy;
	char		buf_i[D_SIZE];
	char		buf_f[D_SIZE];

	ft_bzero(buf_i, D_SIZE);
	ft_bzero(buf_f, D_SIZE);
	d = ft_fabs(d);
	accuracy = f->dot ? f->dot_l : 6;
	accuracy -= (f->g && accuracy >= len_fnumber(f, d)) ?
	len_fnumber(f, d) : 0;
	accuracy = accuracy > 308 ? 308 : accuracy;
	buf_float(d, buf_f, accuracy, f);
	buf_integer(d, buf_i, accuracy, f);
	ft_strcat(buf_i, ".");
	ft_strcat(buf_i, buf_f);
	float_params(buf_i, f);
	return (ft_putstr(buf_i) + ((f->g) ? 0 : print_space_ch(f->dot_l -
	((int)ft_strlen(buf_i) - len_fnumber(f, d) - 1), '0')));
}

double	get_float(double d)
{
	int			i;
	double		ld;

	if (d <= LLONG_MAX)
		ld = d - (long long)d;
	else
	{
		i = 1;
		ld = d;
		while ((ld = ld / 10) > 1)
			i++;
		while (i)
		{
			ld = ld * 10 - (int)(ld * 10);
			i--;
		}
		ld -= (int)ld;
	}
	return (ld);
}

void	buf_float(double d, char buf[D_SIZE], int accuracy, t_flags *f)
{
	int			i;
	int			round;
	double		ld;

	i = 0;
	ld = get_float(d);
	round = (int)(ld * 10);
	ld *= ft_pow(10, accuracy);
	ld = ((int)(get_float(ld) * 10) > 4) ? ld + 0.5 : ld;
	while (accuracy && i < 308)
	{
		buf[--accuracy] = ft_llabs((long long)ld) % 10 + '0';
		buf[accuracy] = (buf[accuracy] == '(') ? '0' : buf[accuracy];
		ld /= 10;
	}
	if (round == 9 && buf[0] == '0')
		f->round = 1;
}

char	*buf_integer(double d, char buf[D_SIZE], int accuracy, t_flags *f)
{
	int			i;
	int			len;
	long double	ld;
	int			round;

	round = (int)(get_float(d) * 10);
	if ((round > 4 && !accuracy) || f->round)
		d += 0.5;
	ld = d;
	len = 0;
	if (d <= LLONG_MAX)
		return (ft_lltobuf(buf, d));
	while (ld >= 1)
	{
		ld /= 10;
		len++;
	}
	buf[0] = (len == 0) ? '0' : 0;
	i = 0;
	while (len--)
	{
		buf[i++] = (int)(ld * 10) % 10 + '0';
		ld = (ld * 10) - ((int)(ld * 10));
	}
	return (buf);
}

void	float_params(char buf[D_SIZE], t_flags *f)
{
	int			i;

	i = 0;
	if (!f->hash && f->dot && !f->dot_l)
		while (buf[i])
		{
			if (buf[i] == '.')
			{
				buf[i] = 0;
				break ;
			}
			i++;
		}
	if (f->g)
		float_gparams(buf);
}
