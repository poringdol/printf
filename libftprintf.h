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
# define f_ll flags->ll
# define f_hex flags->hex
# define f_hash flags->hash

typedef struct	s_flags
{
	char		minus;
	char		plus;
	char		hidden;
	char		zero;
	char		dot;
	char		sign;
	char		intzero;
	char		ll;
	char		hex;
	char		hash;
	int			spaces_len;
	int			zero_len;
	int			dot_len;
}				t_flags;

int				ft_printf(const char *format, ... );
int				print_c(va_list *ap,  t_flags *flags);
int				print_s(va_list *ap, t_flags *flags);
int				print_number(va_list *ap, t_flags *flags, char c);
int				print_i(va_list *ap, t_flags *flags);
int				print_u(va_list *ap, t_flags *flags);
int				print_li(va_list *ap, t_flags *flags);
int				print_lli(va_list *ap, t_flags *flags);
int			 	check_params(char **format, va_list *ap, t_flags *flags);
int				get_number(char **arr);
int				len_number(t_flags *flags, long long n);
int				ft_putunbr(unsigned n);
int				isspecs(char c);
int				isflags(char c);
int				print_spaces(int len, int c);
t_flags			*create_flags(void);
void			reset_flags(t_flags *flags);
void			ignored_flag(t_flags *flags);
void			set_flags(va_list *ap, t_flags *flags, char **c, int **last_flag);

#endif