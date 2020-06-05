#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int isinfnan(double *d)
{
	if (*((unsigned long *)(d)) == DBL_INF ||
	*((unsigned long *)(d)) == DBL_NINF ||
	*((unsigned long *)(d)) == DBL_NAN ||
	*((unsigned long *)(d)) == DBL_NZERO)
		return (1);
	return (0);
}
int	print_infnan(t_flags *flags, double *d)
{
	int		n;
	int		len;
	int		spaces;
	char	*string;

	n = 0;
	if (*((unsigned long *)(d)) == DBL_NAN)
		string = "nan";
	else if (*((unsigned long *)(d)) == DBL_INF)
		string = "inf";
	else if (*((unsigned long *)(d)) == DBL_NINF)
		string = "-inf";
	else if (*((unsigned long *)(d)) == DBL_NZERO)
	{
		flags->nzero = 1;
		flags->sign = 1;
		return (print_f(flags, 0));
	}
	ignored_flags(flags);
	n += print_space_ch(F_ZERO_L - ft_strlen(string), '0');
	len = ft_strlen(string);
	if (F_DOT)
		len = (F_DOT_L < len) ? F_DOT_L : len;
	spaces = F_SPACES_L - len;
	n += (F_MINUS ? (ft_putnstr(string, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(string, len));
	return (n);
}