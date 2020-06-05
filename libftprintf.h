/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:51:21 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 12:51:25 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define DBL_INF    0x7FF0000000000000
# define DBL_NINF   0xFFF0000000000000
# define DBL_NAN    0x7FF0000000100000
# define DBL_PZERO  0x0000000000000000
# define DBL_NZERO  0x8000000000000000
# define LDBL_INF   0x7FFF0000000000000000L
# define LDBL_NINF  0xFFFF0000000000000000L
# define LDBL_NAN   0x7FFF0000000001000000L
# define FTPF_LDBL_INF  0x8000000000000000

# define D_SIZE 330

# define F_MINUS flags->minus
# define F_PLUS flags->plus
# define F_HIDDEN flags->hidden
# define F_ZERO flags->zero
# define F_DOT flags->dot
# define F_SIGN flags->sign
# define F_INTZERO flags->intzero
# define F_SPACES_L flags->spaces_len
# define F_ZERO_L flags->zero_len
# define F_DOT_L flags->dot_len
# define F_LL flags->ll
# define F_HH flags->hh
# define F_HEX flags->hex
# define F_UNSIGN flags->unsign
# define F_OCT flags->oct
# define F_HASH flags->hash
# define F_NZERO flags->nzero
# define F_LAST_F flags->last_flag

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
	char		hh;
	char		hex;
	char		unsign;
	char		oct;
	char		hash;
	char		e;
	char		g;
	char		round;
	char		nzero;
	int			*last_flag;
	int			spaces_len;
	int			zero_len;
	int			dot_len;
}				t_flags;

int				ft_printf(const char *format, ...);
int				print_c(va_list *ap, t_flags *flags);
int				print_s(va_list *ap, t_flags *flags);
int				print_number(va_list *ap, t_flags *flags, char c);
int				print_i(va_list *ap, t_flags *flags);
int				print_hi(va_list *ap, t_flags *flags);
int				print_hhi(va_list *ap, t_flags *flags);
int				print_lli(va_list *ap, t_flags *flags);
int				print_u(va_list *ap, t_flags *flags);
int				print_lu(va_list *ap, t_flags *flags);
int				print_llu(va_list *ap, t_flags *flags);
int				print_x(va_list *ap, t_flags *flags, char c);
int				print_llx(va_list *ap, t_flags *flags, char c);
int				print_p(va_list *ap, t_flags *flags);
int				print_o(va_list *ap, t_flags *flags, char c);
int				print_llo(va_list *ap, t_flags *flags, char c);
int				print_f(t_flags *flags, double d);
int				print_e(t_flags *flags, double d);
int				print_g(t_flags *flags, double d);
int				print_lf(va_list *ap, t_flags *flags);
int				print_feg(va_list *ap, t_flags *flags, int c);
int				print_percent(t_flags *flags);
int				print_space_ch(int len, int c);
int				nospec(t_flags *flags, char c);
int				check_params(char **format, va_list *ap, t_flags *flags, int n);
int				ft_putnstr(char const *s, int n);
int				print_space_ch(int n, int c);
int				print_space_num(t_flags *flags, int len);
int				plus_minus(t_flags *flags, double n, int c);
int				print_dot(t_flags *flags, int len);
int				print_sign(t_flags *flags);
int				print_percent(t_flags *flags);
int				get_number(char **arr);
int				put_number(long long n);
int				len_number(t_flags *flags, long long n);
int				len_unumber(unsigned long long n);
int				isspecs(char c);
int				isflags(char c);
int				get_number(char **arr);
void			ifnegative(t_flags *flags);
int				islongshort(va_list *ap, t_flags *flags, char **str);
t_flags			*create_flags(void);
void			reset_flags(t_flags *flags);
void			ignored_flags(t_flags *flags);
void			set_flags(va_list *ap, t_flags *flags, char **c);
void			buf_integer(double d, char buf[D_SIZE], int accuracy,\
				t_flags *flags);
int				len_fnumber(t_flags *flags, double f);
double			get_float(double d);
void			buf_float(double d, char buf[D_SIZE], int accuracy,\
				t_flags *flags);
void			float_params(char buf[D_SIZE], t_flags *flags);
int				print_float(t_flags *flags, double f);
int				len_enumber(double *f);
int				print_efloat(t_flags *flags, double f);
void			float_gparams(char buf[D_SIZE]);
int				isinfnan(double *d);
int				print_infnan(t_flags *flags, double *d);

#endif
