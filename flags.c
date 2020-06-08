/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:28:25 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 10:28:30 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

static void	set_last(t_flags *f, int c)
{
	if (c == '0' && !f->last_flag)
	{
		f->zero = 1;
		f->last_flag = &(f->zero_l);
	}
	else if (c == '.')
	{
		f->dot = 1;
		f->last_flag = &(f->dot_l);
	}
	else if (c == '-')
	{
		if (f->last_flag == &(f->zero_l))
		{
			f->zero = 0;
			f->last_flag = NULL;
			f->spaces_l = (!f->spaces_l && f->zero_l) ?
			f->zero_l : f->spaces_l;
		}
		f->minus = 1;
	}
}

t_flags		*create_flags(void)
{
	t_flags *f;

	if (!(f = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	f->minus = 0;
	f->plus = 0;
	f->hidden = 0;
	f->zero = 0;
	f->dot = 0;
	f->spaces_l = 0;
	f->zero_l = 0;
	f->dot_l = 0;
	f->sign = 0;
	f->intzero = 0;
	f->ll = 0;
	f->hh = 0;
	f->hex = 0;
	f->unsign = 0;
	f->oct = 0;
	f->e = 0;
	f->g = 0;
	f->round = 0;
	f->nzero = 0;
	f->last_flag = NULL;
	return (f);
}

void		set_flags(va_list *ap, t_flags *f, char **c)
{
	if (**c == '-' && !f->dot)
		set_last(f, **c);
	else if (**c == '+')
		f->plus = 1;
	else if (**c == ' ')
		f->hidden = 1;
	else if (**c == '0' && !f->last_flag && !f->minus)
		set_last(f, **c);
	else if (**c == '.')
		set_last(f, **c);
	else if (**c == '*' || ft_isdigit(**c))
	{
		if (f->last_flag)
			*f->last_flag = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		else
			f->spaces_l = (**c == '*' ? va_arg(*ap, int) : get_number(c));
		f->last_flag = NULL;
	}
	else if (**c == 'l' || **c == 'L')
		f->ll++;
	else if (**c == 'h')
		f->hh++;
	else if (**c == '#')
		f->hash = 1;
	(*c)++;
}

void		reset_flags(t_flags *f)
{
	f->minus = 0;
	f->plus = 0;
	f->hidden = 0;
	f->zero = 0;
	f->dot = 0;
	f->spaces_l = 0;
	f->zero_l = 0;
	f->dot_l = 0;
	f->sign = 0;
	f->intzero = 0;
	f->ll = 0;
	f->hh = 0;
	f->hex = 0;
	f->unsign = 0;
	f->oct = 0;
	f->hash = 0;
	f->e = 0;
	f->g = 0;
	f->round = 0;
	f->nzero = 0;
	f->last_flag = NULL;
}

void		ignored_flags(t_flags *f)
{
	if (f->plus)
		f->hidden = 0;
	if (f->minus)
	{
		f->spaces_l = !f->spaces_l ? f->zero_l : f->spaces_l;
		f->zero = 0;
		f->zero_l = 0;
	}
	if (f->dot && f->zero)
	{
		f->spaces_l = f->zero_l;
		f->zero_l = 0;
		f->zero = 0;
	}
	if (f->plus || f->hidden)
		f->sign = 1;
	if (f->hash && f->intzero)
		f->hash = 0;
	if (f->hash && !f->intzero && f->dot && f->hex)
		f->dot_l += 2;
	if (f->unsign && f->plus)
	{
		f->plus = 0;
		f->hidden = 1;
	}
}
