#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>
#include <unistd.h>

typedef struct s_flags
{
	int minus;
	int dot;
	int zero;
	int star;
} t_flags;

int		ft_printf(const char *format, ... );
int 	check_params(char **format, va_list *ap);

#endif