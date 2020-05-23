#include "libftprintf.h"
#include "libft.h"

int	ft_putunbr(unsigned n)
{
	long long	i;
	long long	tmp;
	int			len;

	if (n == 0)
		return (ft_putchar(0));
	len = 0;
	tmp = n;
	i = 1;
	while (i <= tmp)
		i *= 10;
	if (tmp != 0)
		i /= 10;
	while (i > 0)
	{
		ft_putchar(tmp / i + '0');
		tmp %= i;
		i /= 10;
		len++;
	}
	return (len);
}