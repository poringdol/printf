#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_flags
{
	char minus;
	char zero;
	char dot;
	int spaces_len;
	int zero_len;
	int dot_len;
}	t_flags;

int		ft_printf(const char *format, ... );
int		print_char(va_list *ap,  t_flags *flags);
int		print_string(va_list *ap, t_flags *flags);
int 	check_params(char **format, va_list *ap, t_flags *flags);
int		get_number(char **arr);
int		isspecs(char c);
int		isflags(char c);
int		print_spaces(int n);
t_flags *create_flags(void);
void	reset_flags(t_flags *flags);
void	set_flags(va_list *ap, t_flags *flags, char **c, int **last_flag);

#endif