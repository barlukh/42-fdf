/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:52:08 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 11:05:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	int		sign;
	int		n;

	i = 0;
	sign = 1;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	n = 0;
	while (s[i] != '\0')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	n = n * sign;
	return (n);
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
