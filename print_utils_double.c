#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

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
	float_params(buf_i, flags);
	return (ft_putstr(buf_i));
}

void			get_double(double d, char buf[D_SIZE])
{
	int			len;

	len = len_unumber((long long)d);
	while (len--)
	{
		buf[len] = (long long)d % 10 + '0';
		d /= 10;
	}
}

void			get_fraction(double d, char buf[D_SIZE], int accuracy)
{
	int			i;
	long long	tmp;
	
	i = 0;
	d = (d - (long long)d) * ft_pow(10, accuracy + 1);
	tmp = ((long long)d % 10 > 4) ? d / 10 + 1 : d / 10;
	while (accuracy--)
	{
		buf[accuracy] = tmp % 10 + '0';
		tmp /= 10;
	}
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