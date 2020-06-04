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

int				len_fnumber(t_flags *flags, double f)
{
	double	i;
	double	tmp;
	int		len;

	len = !flags->sign ? 0 : 1;
	tmp = f > 0 ? f : -f;
	i = 1;
	while (i <= tmp)
	{
		if (i * 10 < i)
			return (++len);
		i *= 10;
		len++;
	}
	return (f ? len : ++len);
}

int			len_enumber(double *f)
{
	int		len;

	*f = (*f < 0) ? -*f : *f;
	len = 0;
	while (*f < 1)
	{
		*f *= 10;
		len++;
	}
	while (*f > 10)
	{
		*f /= 10;
		len++;
	}
	return (len);
}

int				print_efloat(t_flags *flags, double d)
{
	int			accuracy;
	int			len_e;
	char		sign[2];
	char		buf_i[D_SIZE];
	char		buf_f[D_SIZE];

	ft_bzero(sign, 2);
	ft_bzero(buf_i, D_SIZE);
	ft_bzero(buf_f, D_SIZE);
	(d < 1) ? ft_strcat(sign, "-") : ft_strcat(sign, "+");
	d = (d >= 0) ? d : -d;
	len_e = len_enumber(&d);
	get_double(d, buf_i);
	accuracy = F_DOT ? F_DOT_L : 6;
	ft_strcat(buf_i, ".");
	get_fraction(d, buf_f, accuracy);
	ft_strcat(buf_i, buf_f);
	float_params(buf_i, flags);
	ft_strcat(buf_i, "e");
	ft_strcat(buf_i, sign);
	ft_itoa_e(len_e, buf_f);
	ft_strcat(buf_i, buf_f);
	return (ft_putstr(buf_i));
}