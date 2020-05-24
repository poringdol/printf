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

# define F_MINUS flags->minus
# define F_PLUS flags->plus
# define F_HIDDEN flags->hidden
# define F_ZERO flags->zero
# define F_DOT flags->dot
# define F_SIGN flags->sign
# define F_INTZERO flags->intzero
# define F_SPACES_L flags->spaces_len
# define F_ZERO_L flags->zero_len
# define F_DOL_L flags->dot_len
# define F_LL flags->ll
# define F_HH flags->hh
# define F_HEX flags->hex
# define F_HASH flags->hash
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
	char		hash;
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
int				print_u(va_list *ap, t_flags *flags);
int				print_lli(va_list *ap, t_flags *flags);
int				print_hhi(va_list *ap, t_flags *flags);
int				print_p(va_list *ap, t_flags *flags);
int				print_x(va_list *ap, t_flags *flags, char c);
int				print_percent(t_flags *flags);
int				print_space_ch(int len, int c);
int				check_params(char **format, va_list *ap, t_flags *flags, int n);
int				print_space_ch(int n, int c);
int				print_space_num(t_flags *flags, int len);
int				plus_minus(t_flags *flags, long long n, int c);
int				print_dot(t_flags *flags, int len);
int				print_sign(t_flags *flags);
int				print_percent(t_flags *flags);
int				get_number(char **arr);
int				put_number(long long n);
int				len_number(t_flags *flags, long long n);
int				isspecs(char c);
int				isflags(char c);
int				get_number(char **arr);
void			ifnegative(t_flags *flags);
int				islongshort(va_list *ap, t_flags *flags, char **str);
t_flags			*create_flags(void);
void			reset_flags(t_flags *flags);
void			ignored_flags(t_flags *flags);
void			set_flags(va_list *ap, t_flags *flags, char **c);

#endif
