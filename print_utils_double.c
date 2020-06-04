/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 00:47:39 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 00:50:23 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
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
	get_fraction(d, buf_f, accuracy, flags);
	get_double(d, buf_i, accuracy, flags);
	ft_strcat(buf_i, ".");
	ft_strcat(buf_i, buf_f);
	float_params(buf_i, flags);
	return (ft_putstr(buf_i));
}

void	get_double(double d, char buf[D_SIZE], int accuracy, t_flags *flags)
{
	int			len;
	long long	tmp;
	long long	round;

	round = (long long)((d - (long long)d) * 10);
	tmp = (long long)d;
	if ((round > 4 && !accuracy) || flags->round)
		tmp++;
	len = len_unumber(tmp);
	while (len--)
	{
		buf[len] = tmp % 10 + '0';
		tmp /= 10;
	}
}

void	get_fraction(double d, char buf[D_SIZE], int accuracy, t_flags *flags)
{
	int			round;
	long long	tmp;

	round = (int)((d - (long long)d) * 10);
	d = (d - (long long)d) * ft_pow(10, accuracy + 1);
	tmp = ((long long)d % 10 > 4) ? d / 10 + 1 : d / 10;
	while (accuracy--)
	{
		buf[accuracy] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (round == 9 && buf[0] == '0')
		flags->round = 1;
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
				break;
			}
			i++;
		}
	if (flags->g)
		float_gparams(buf);
}
