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
	if (c == '-' || c == '0' || c == '.' || c == '*' ||
	c == '#' || c == ' ' || c == '+' || ft_isdigit(c))
		return (c);
	return (0);
}

int		isspecs(char c)
{
	if (c == 'c' || c == 's' || c == 'i' || c == 'd' || c == 'u' ||
	c == 'x' || c == 'X' || c == 'l' || c == 'h' || c == 'p')
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

void	ifnegative(t_flags *flags)
{
	if (F_ZERO_L < 0 || F_SPACES_L < 0)
	{
		F_ZERO_L = F_ZERO_L < 0 ? -F_ZERO_L : F_ZERO_L;
		F_SPACES_L = F_SPACES_L < 0 ? -F_SPACES_L : F_SPACES_L;
		F_MINUS = 1;
	}
	if (F_DOT_L < 0 && (F_DOT_L < F_SPACES_L || F_DOT_L < F_ZERO_L))
	{
		F_DOT_L = 0;
		F_DOT = 0;
	}
}

int		islongshort(va_list *ap, t_flags *flags, char **str)
{
	while (**str == 'l')
		set_flags(ap, flags, str);
	while (**str == 'h')
		set_flags(ap, flags, str);
	return (print_number(ap, flags, **str));
}
