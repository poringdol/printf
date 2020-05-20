#include <stdarg.h>
#include <unistd.h>
#include "printf.h"
#include "libft.h"

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd')
		return (c);
	return (0);
}

int		print_spaces(int n)
{
	int i;

	i = 0;
	while (i++ < n)
		ft_putchar(' ');
	return (n);
}

void	reset_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->dot = 0;
	flags->star = 0;
	flags->zero = 0;
}

void	set_flags(t_flags *flags, char c)
{
	if (c == '-')
		flags->minus = 1;
	else if (c == '0')
		flags->zero = 1;
	else if (c == '.')
		flags->dot = 1;
	else if (c == '*')
		flags->star = 1;
}

int get_number(char *arr, int *i)
{
	int 	j;
	int		k;
	char	str[12];

	j = *i;
	k = 0;
	while (arr[j] && j < 20 && ft_isdigit(arr[j]))
		str[k++] = arr[j++];
	str[k] = '\0';
	*i = j - 1;
	return (ft_atoi(str));
}

int		print_char(va_list *ap, char arr[])
{
	int i;
	int	minus;
	int count;

	i = 0;
	count = 0;
	minus = 0;
	while (arr[i])
	{
		if (arr[i] == '-')
			minus = 1;
		else if (arr[i] == '*')
			count = va_arg(*ap, int);
		else if (ft_isdigit(arr[i]))
			count = get_number(arr, &i) - 1;
		i++;
	}
	return (minus ? (ft_putchar(va_arg(*ap, int)) + print_spaces(count)) :
	print_spaces(count) + ft_putchar(va_arg(*ap, int)));
}

int 	check_params(char **str, va_list *ap)
{
	char	arr[50];
	int		n;
	char	*tmp;

	n = 0;
	tmp = *str;
	ft_bzero(arr, 50);
	if (*tmp == '%')
		return (ft_putchar(*tmp++));
	while (!isspecs(*tmp))
		arr[n++] = *tmp++;
	if (*tmp == 'c')
		n = print_char(ap, arr);
	// else if (*format == 's')
	// 	n += print_string(va_arg(ap, char *));
	// else if (*format == 'i' || *format == 'd')
	// 	n = print_number(va_arg(ap, int));
	*str = tmp;
	return (n);
}