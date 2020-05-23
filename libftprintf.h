#ifndef LIBFTPRINTf_hidden
# define LIBFTPRINTf_hidden

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define f_minus flags->minus
# define f_plus flags->plus
# define f_hidden flags->hidden
# define f_zero flags->zero
# define f_dot flags->dot
# define f_sign flags->sign
# define f_intzero flags->intzero
# define f_spaces_l flags->spaces_len
# define f_zero_l flags->zero_len
# define f_dot_l flags->dot_len

typedef struct	s_flags
{
	char		minus;
	char		plus;
	char		hidden;
	char		zero;
	char		dot;
	char		sign;
	char		intzero;
	int			spaces_len;
	int			zero_len;
	int			dot_len;
}				t_flags;

int				ft_printf(const char *format, ... );
int				print_char(va_list *ap,  t_flags *flags);
int				print_string(va_list *ap, t_flags *flags);
int				print_number(va_list *ap, t_flags *flags);
int				print_unumber(va_list *ap, t_flags *flags);
int			 	check_params(char **format, va_list *ap, t_flags *flags);
int				get_number(char **arr);
int				len_number(t_flags *flags, int n);
int				ft_putunbr(unsigned n);
int				isspecs(char c);
int				isflags(char c);
int				print_spaces(int n, int c);
t_flags			*create_flags(void);
void			reset_flags(t_flags *flags);
void			ignored_flag(t_flags *flags);
void			set_flags(va_list *ap, t_flags *flags, char **c, int **last_flag);

#endif