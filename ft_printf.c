/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:57:20 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/05 08:35:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_parse_index(const char *s, size_t *i, int *count, va_list *args);
static int	ft_parse_format_specifier(char c, va_list *args);

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;
	size_t	i;

	if (!s)
		return (-1);
	va_start(args, s);
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		ft_parse_index(s, &i, &count, &args);
		if (count == -1)
			return (va_end(args), -1);
	}
	va_end(args);
	return (count);
}

// Parses each character of the formatted string
static void	ft_parse_index(const char *s, size_t *i, int *count, va_list *args)
{
	int	check;

	check = 0;
	if (s[*i] != '%')
	{
		if (ft_putchar(s[(*i)]) == -1)
		{
			*count = -1;
			return ;
		}
		(*count)++;
		(*i)++;
	}
	else
	{
		check = ft_parse_format_specifier(s[(*i) + 1], args);
		if (check == -1)
		{
			*count = -1;
			return ;
		}
		*count += check;
		*i += 2;
	}
}

// Parses each variadic argument of the format specifier
static int	ft_parse_format_specifier(char c, va_list *args)
{
	if (c == '%')
		return (ft_putchar(c));
	else if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, const char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_s(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_putnbr_u(va_arg(*args, unsigned int), BASE10, DECIMAL));
	else if (c == 'x')
		return (ft_putnbr_u(va_arg(*args, unsigned int), BASE16, HEX_LCASE));
	else if (c == 'X')
		return (ft_putnbr_u(va_arg(*args, unsigned int), BASE16, HEX_UCASE));
	else if (c == 'p')
		return (ft_putnbr_p(va_arg(*args, uintptr_t)));
	else
		return (-1);
}
