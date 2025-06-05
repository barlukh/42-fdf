/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:07:57 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/05 08:35:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_p(uintptr_t p)
{
	int	count;
	int	check;

	if (p == 0)
		return (ft_putstr("(nil)"));
	count = 0;
	if (p < BASE16)
	{
		check = ft_putstr("0x");
		if (check == -1)
			return (-1);
		count += check;
	}
	if (p >= BASE16)
	{
		check = ft_putnbr_p(p / BASE16);
		if (check == -1)
			return (-1);
		count += check;
	}
	if (ft_putchar(HEX_LCASE[p % BASE16]) == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_putnbr_s(int n)
{
	int	count;
	int	check;

	if (n == INT_MIN)
		return (ft_putstr("-2147483648"));
	count = 0;
	if (n < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		count++;
		n = -n;
	}
	if (n >= BASE10)
	{
		check = ft_putnbr_s(n / BASE10);
		if (check == -1)
			return (-1);
		count += check;
	}
	if (ft_putchar(DECIMAL[n % BASE10]) == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_putnbr_u(unsigned int n, unsigned int base, const char *style)
{
	int	count;
	int	check;

	count = 0;
	if (n >= base)
	{
		check = ft_putnbr_u(n / base, base, style);
		if (check == -1)
			return (-1);
		count += check;
	}
	if (ft_putchar(style[n % base]) == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_putstr(const char *s)
{
	int	count;

	if (!s)
		s = "(null)";
	count = 0;
	while (s[count] != '\0')
	{
		if (ft_putchar(s[count]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
