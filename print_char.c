#include <stdarg.h>
#include "libft.h"
#include "libftprintf.h"

int			print_c(va_list *ap,  t_flags *flags)
{
	int spaces;
	int	n;

	spaces = flags->spaces_len - 1;
	n = flags->minus ? (ft_putchar(va_arg(*ap, int)) + print_spaces(spaces, ' ')) :
	print_spaces(spaces, ' ') + ft_putchar(va_arg(*ap, int));
	return (n);
}
