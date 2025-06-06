/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:17:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 11:47:44 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

char	*ft_line_read(int fd, char **buf, t_struct *var)
{
	var->br = ft_strchr(var->cache, '\n');
	while (!var->br)
	{
		var->read_bytes = read(fd, *buf, BUFFER_SIZE);
		if (var->read_bytes <= 0)
		{
			if (var->read_bytes == 0 && *var->cache)
			{
				var->br = ft_strchr(var->cache, '\0') - 1;
				return (var->br);
			}
			free(*buf);
			free(var->cache);
			return (*buf = NULL);
		}
		var->cache = ft_strjoin(*buf, var);
		if (!var->cache)
		{
			free(*buf);
			free(var->cache);
			return (*buf = NULL);
		}
		var->br = ft_strchr(var->cache, '\n');
	}
	return (var->br);
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *buf, t_struct *var)
{
	size_t	cache_len;
	char	*new_cache;

	if (!buf || !var->cache)
		return (NULL);
	cache_len = 0;
	while (var->cache[cache_len] != '\0')
		cache_len++;
	new_cache = malloc(sizeof(char) * (cache_len + var->read_bytes + 1));
	if (!new_cache)
		return (NULL);
	ft_memcpy(new_cache, var->cache, cache_len);
	ft_memcpy(new_cache + cache_len, buf, var->read_bytes);
	new_cache[cache_len + var->read_bytes] = '\0';
	free(var->cache);
	return (new_cache);
}

char	*ft_substr_gnl(char **s, size_t len)
{
	char	*substr;
	size_t	i;

	if (!*s)
		return (NULL);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
	{
		free(*s);
		*s = NULL;
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		substr[i] = (*s)[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
