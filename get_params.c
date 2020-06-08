/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 11:20:47 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/24 11:21:13 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

int		isflags(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '*' || c == '#' ||
	c == ' ' || c == '+' || ft_isdigit(c))
		return (c);
	return (0);
}

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u' ||
	c == 'x' || c == 'X' || c == 'l' || c == 'h' || c == 'p' ||
	c == 'L' || c == 'e' || c == 'g')
		return (c);
	return (0);
}

int		get_number(char **arr)
{
	int		k;
	char	*tmp;
	char	str[12];

	k = 0;
	tmp = *arr;
	while (*tmp && ft_isdigit(*tmp))
		str[k++] = *tmp++;
	str[k] = '\0';
	*arr = --tmp;
	return (ft_atoi(str));
}

void	ifnegative(t_flags *f)
{
	if (f->zero_l < 0 || f->spaces_l < 0)
	{
		f->zero_l = f->zero_l < 0 ? -f->zero_l : f->zero_l;
		f->spaces_l = f->spaces_l < 0 ? -f->spaces_l : f->spaces_l;
		f->minus = 1;
	}
	if (f->dot_l < 0 && (f->dot_l < f->spaces_l || f->dot_l < f->zero_l))
	{
		f->dot_l = 0;
		f->dot = 0;
	}
}

int		islongshort(va_list *ap, t_flags *f, char **str)
{
	while (**str == 'l' || **str == 'L')
		set_flags(ap, f, str);
	while (**str == 'h')
		set_flags(ap, f, str);
	if (**str == 'f')
		return (print_lf(ap, f));
	return (print_number(ap, f, **str));
}
