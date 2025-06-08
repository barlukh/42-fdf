/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:17:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/08 13:52:59 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char	*ft_line_read(int fd, char *buf, t_gnl *var);
static char	*ft_strjoin_gnl(char *buf, t_gnl *var);
static char	*ft_substr_gnl(char *s, size_t len);

char	*ft_get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	t_gnl		var;

	var.cache = ft_substr_gnl(buf, ft_strchr(buf, '\0') - buf);
	if (!var.cache)
		return (NULL);
	if (ft_line_read(fd, buf, &var) == NULL)
		return (NULL);
	var.new_line = ft_substr_gnl(var.cache, var.br - var.cache + 1);
	if (!var.new_line)
	{
		free(var.cache);
		return (NULL);
	}
	ft_memcpy(buf, var.br + 1, ft_strchr(var.br + 1, '\0') - var.br);
	free(var.cache);
	return (var.new_line);
}

// Reads from a file looking for a linebreak or EOF
static char	*ft_line_read(int fd, char *buf, t_gnl *var)
{
	var->br = ft_strchr(var->cache, '\n');
	while (!var->br)
	{
		var->read_bytes = read(fd, buf, BUFFER_SIZE);
		if (var->read_bytes <= 0)
		{
			if (var->read_bytes == 0 && *var->cache)
			{
				var->br = ft_strchr(var->cache, '\0') - 1;
				return (var->br);
			}
			free(var->cache);
			return (NULL);
		}
		var->cache = ft_strjoin_gnl(buf, var);
		if (!var->cache)
			return (NULL);
		var->br = ft_strchr(var->cache, '\n');
	}
	return (var->br);
}

// Joins two strings together (cache with the readout from a buffer)
static char	*ft_strjoin_gnl(char *buf, t_gnl *var)
{
	size_t	cache_len;
	char	*new_cache;

	cache_len = 0;
	while (var->cache[cache_len] != '\0')
		cache_len++;
	new_cache = malloc(sizeof(char) * (cache_len + var->read_bytes + 1));
	if (!new_cache)
	{
		free(var->cache);
		return (NULL);
	}
	ft_memcpy(new_cache, var->cache, cache_len);
	ft_memcpy(new_cache + cache_len, buf, var->read_bytes);
	new_cache[cache_len + var->read_bytes] = '\0';
	free(var->cache);
	return (new_cache);
}

// Creates a new substring of specified length from a string
static char	*ft_substr_gnl(char *s, size_t len)
{
	char	*substr;
	size_t	i;

	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
