/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:52:08 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/12 15:15:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_atoi_base(const char *s)
{
	int	n;
	int	base;

	n = 0;
	base = 10;
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
	{
		base = 16;
		s += 2;
	}
	while (*s)
	{
		n *= base;
		if (*s >= '0' && *s <= '9')
			n += *s - '0';
		else if (base == 16 && *s >= 'A' && *s <= 'F')
			n += *s - 'A' + 10;
		else if (base == 16 && *s >= 'a' && *s <= 'f')
			n += *s - 'a' + 10;
		else
			break ;
		s++;
	}
	return (n);
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
