#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int			print_lc(va_list *ap, t_flags *f)
{
	int     spaces;
	int	    n;
	char     ch;

	n = 0;
	ch = (char)va_arg(*ap, wchar_t);
	spaces = f->spaces_l - 1;
	n += print_space_ch(f->zero_l - 1, '0');
	n += f->minus ? (ft_putchar(ch) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putchar(ch);
	return (n);
}

int				print_ls(va_list *ap, t_flags *f)
{
	int		n;
	int		len;
	int		spaces;
	wchar_t	*string;
	char    convert[S_SIZE];

	n = 0;
	if (!(string = va_arg(*ap, wchar_t *)))
		return (print_null(f));
	while (*string != '\0')
		convert[n++] = *((char *)string++);
	convert[n] = '\0';
	len = ft_strlen(convert);
	ignored_flags(f);
	n = print_space_ch(f->zero_l - ft_strlen(convert), '0');
	if (f->dot)
		len = (f->dot_l < len) ? f->dot_l : len;
	spaces = f->spaces_l - len;
	n += (f->minus ? (ft_putnstr(convert, len) + print_space_ch(spaces, ' ')) :
	print_space_ch(spaces, ' ') + ft_putnstr(convert, len));
	return (n);
}
