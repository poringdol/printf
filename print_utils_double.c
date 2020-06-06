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
// #include <stdio.h>
#include "libftprintf.h"
#include "libft.h"

int		print_float(t_flags *flags, double d)
{
	int			accuracy;
	char		buf_i[D_SIZE];
	char		buf_f[D_SIZE];

	ft_bzero(buf_i, D_SIZE);
	ft_bzero(buf_f, D_SIZE);
	d = (d >= 0) ? d : -d;
	accuracy = F_DOT ? F_DOT_L : 6;
	accuracy = accuracy > 308 ? 308 : accuracy;
	buf_float(d, buf_f, accuracy, flags);
	buf_integer(d, buf_i, accuracy, flags);
	ft_strcat(buf_i, ".");
	ft_strcat(buf_i, buf_f);
	float_params(buf_i, flags);
	// reset_flags(flags);
	return (ft_putstr(buf_i) + (flags->g) ? 0 :
	print_space_ch(F_DOT_L - (1 + len_fnumber(flags, d) + (int)ft_strlen(buf_i)), '0'));
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

void	buf_float(double d, char buf[D_SIZE], int accuracy, t_flags *flags)
{
	int			i;
	int			accur_tmp;
	int			round;
	double		ld;

	i = 0;
	ld = get_float(d);
	round = (int)(ld * 10);
	accur_tmp = accuracy;
	ld *= ft_pow(10, accuracy);
	// while (accur_tmp-- && i < 308)
	// {
	// 	ld *= 10;
	// 	i++;
	// }
	ld = ((int)(get_float(ld) * 10) > 4) ? ld + 1 : ld;
	// while (accur_tmp--)
	// 	ld /= 10;
	while (accuracy && i < 308)
	{
		// printf("%f\n", ld);
		// printf("%lli\n", (long long)ld % 10 + '0');
		buf[--accuracy] = ft_llabs((long long)ld) % 10 + '0';
		buf[accuracy] = (buf[accuracy] == '(') ? '0' : buf[accuracy];
		ld /= 10;
	}
	if (round == 9 && buf[0] == '0')
		flags->round = 1;
}

void	buf_integer(double d, char buf[D_SIZE], int accuracy, t_flags *flags)
{
	int			i;
	int			len;
	long double	ld;
	int			round;

	round = (int)(get_float(d) * 10);
	if ((round > 4 && !accuracy) || flags->round)
		d++;
	ld = d;
	len = 0;
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
}

void	float_params(char buf[D_SIZE], t_flags *flags)
{
	int			i;

	i = 0;
	if (!F_HASH && F_DOT && !F_DOT_L)
		while (buf[i])
		{
			if (buf[i] == '.')
			{
				buf[i] = 0;
				break ;
			}
			i++;
		}
	if (flags->g)
		float_gparams(buf);
}
