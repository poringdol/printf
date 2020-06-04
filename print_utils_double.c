#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

void			round_f(char buf[D_SIZE])
{
	int			i;
	int			flag;

	i = ft_strlen(buf) - 1;
	flag = 1;
	while (flag)
	{
		if (buf[i] < '6')
			flag = 0;
		else
			while (flag && i-- && buf[i])
			{
				if (buf[i] < '9' && buf[i] != '.')
				{
					buf[i] += 1;
					flag = 0;
				}
				else if (buf[i] != '.')
					buf[i] = '0';
			}
	}
	buf[ft_strlen(buf) - 1] = 0;
}

int				print_float(t_flags *flags, double f)
{
	int			accuracy;
	char		buf_i[D_SIZE];
	char		buf_f[D_SIZE];

	ft_bzero(buf_i, D_SIZE);
	ft_bzero(buf_f, D_SIZE);
	f = (f >= 0) ? f : -f;
	get_double(f, buf_i);
	accuracy = F_DOT ? F_DOT_L : 6;
	ft_strcat(buf_i, ".");
	get_fraction(f, buf_f, accuracy);
	ft_strcat(buf_i, buf_f);
	round_f(buf_i);
	float_params(buf_i, flags);
	return (ft_putstr(buf_i));
}

void			get_double(double d, char buf[D_SIZE])
{
	double		delim;
	double		tmp;
	int			i;
	char		buf_tmp[D_SIZE];

	i = 0;
	ft_bzero(buf_tmp, D_SIZE);
	if ((int)d == 1)
	{
		buf[0] = '1';
		return ;
	}
	delim = 1e+308;
	while (delim > 1 && d > 0)
	{
		buf_tmp[i++] = (int)(d / delim) + '0';
		tmp = (int)(d / delim) * delim;
		d -= tmp;
		delim /= 10;
	}
	i = 0;
	while (buf_tmp[i] == '0')
		i++;
	ft_strcpy(buf, &buf_tmp[i]);
	buf[0] = (buf[0] == 0) ? '0' : buf[0];
}

void			get_fraction(double d, char buf[D_SIZE], int accuracy)
{
	int			i;

	i = 0;
	d = d - (long long)d;
	while (accuracy + 1 && i < D_SIZE)
	{
		d = d * 10;
		buf[i++] = (int)d % 10 + '0';
		d = d - (long long)d;
		accuracy--;
	}
	d = d * 10;
	if ((int)d % 10 == 9)
		buf [i - 1] += 1;
}


void			float_params(char buf[D_SIZE], t_flags *flags)
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