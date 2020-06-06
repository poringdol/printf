#include <stdarg.h>
#include <float.h>
#include "libftprintf.h"
#include "libft.h"

int isinfnan(double *d)
{
	double d1 = -DBL_MAX + 1 / ft_pow(10, 308);
	double d2 = DBL_MAX - 1 / ft_pow(10, 308);
	if (*((unsigned long *)(d)) == DBL_INF ||
	*((unsigned long *)(d)) == DBL_NINF ||
	*((unsigned long *)(d)) == DBL_NAN ||
	*((unsigned long *)(d)) == DBL_NZERO ||
	*d <= d1 ||
	*d >= d2)
		return (1);
	return (0);
}

static int	get_inftnan(t_flags *flags, char buf[5], double *d)
{
	if (*((unsigned long *)(d)) == DBL_NAN)
		buf = ft_strcpy(buf, "nan");
	else if (*((unsigned long *)(d)) == DBL_INF)
	{
		if (flags->plus || flags->hidden)
			buf = flags->plus ? ft_strcpy(buf, "+inf") : ft_strcpy(buf, " inf");
		else
			buf = ft_strcpy(buf, "inf");
	}
	else if (*((unsigned long *)(d)) == DBL_NINF)
		buf = ft_strcpy(buf, "-inf");
	else if (*((unsigned long *)(d)) == DBL_NZERO)
	{
		flags->nzero = 1;
		flags->sign = 1;
		return (print_f(flags, 0));
	}
	return (0);
}

int	print_infnan(t_flags *flags, double *d)
{
	int		n;
	int		len;
	int		spaces;
	char	buf[5];

	ft_bzero(buf, 5);
	if (*((unsigned long *)(d)) == DBL_NAN ||
	*((unsigned long *)(d)) == DBL_INF || *((unsigned long *)(d)) == DBL_NINF)
		get_inftnan(flags, buf, d);
	else if (*((unsigned long *)(d)) == DBL_NZERO)
		return (get_inftnan(flags, buf, d));
	else if (*d >= DBL_MAX - 1 / ft_pow(10, 308))
		return (print_dblmax());
	else if (*d <= -DBL_MAX + 1 / ft_pow(10, 308))
		return (ft_putchar('-') + print_dblmax());
	ignored_flags(flags);
	len = ft_strlen(buf);
	n = print_space_ch(F_ZERO_L - len, ' ');
	if (F_DOT)
		len = (F_DOT_L < len) ? F_DOT_L : len;
	spaces = F_SPACES_L - len;
	n += (F_MINUS ? (ft_putnstr(buf, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(buf, len));
	return (n);
}

int	print_dblmax(void)
{
	return (ft_putstr("1797693134862315708145274237317043567980705675258449") +
	ft_putstr("965989174768031572607800285387605895586327668781715404589535") +
	ft_putstr("143824642343213268894641827684675467035375169860499105765512") +
	ft_putstr("820762454900903893289440758685084551339423045832369032229481") +
	ft_putstr("658085593321233482747978262041447231687381771809192998812504") +
	ft_putstr("04026184124858368.000000"));
}