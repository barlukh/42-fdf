/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:52:08 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/12 20:53:56 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_atoi_base_loop(const char *s, int base, long long *n);

int	ft_atoi_base(const char *s)
{
	long long	n;
	int			base;
	int			sign;

	n = 0;
	base = 10;
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
	{
		base = 16;
		s += 2;
	}
	ft_atoi_base_loop(s, base, &n);
	return (n * sign);
}

void	ft_free_split(char **line)
{
	size_t	i;

	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptrd;
	const unsigned char	*ptrs;
	size_t				i;

	ptrd = (unsigned char *)dest;
	ptrs = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		i++;
	}
	return (dest);
}

static void	ft_atoi_base_loop(const char *s, int base, long long *n)
{
	while (*s)
	{
		*n *= base;
		if (*s >= '0' && *s <= '9')
			*n += *s - '0';
		else if (base == 16 && *s >= 'A' && *s <= 'F')
			*n += *s - 'A' + 10;
		else if (base == 16 && *s >= 'a' && *s <= 'f')
			*n += *s - 'a' + 10;
		else
			break ;
		s++;
	}
}
