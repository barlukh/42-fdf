/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:17:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 07:33:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char	*ft_read_line(int fd, char *buf, char **cache, char **line_end);
static char	*ft_strjoin_gnl(char *buf, char *cache, ssize_t read_bytes);
static char	*ft_substr_gnl(char *s, size_t len);

char	*ft_get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*cache;
	char		*line_end;
	char		*new_line;

	line_end = NULL;
	cache = ft_substr_gnl(buf, ft_strchr(buf, '\0') - buf);
	if (!cache)
		return (NULL);
	if (ft_read_line(fd, buf, &cache, &line_end) == NULL)
		return (NULL);
	new_line = ft_substr_gnl(cache, line_end - cache + 1);
	if (!new_line)
	{
		free(cache);
		return (NULL);
	}
	ft_memcpy(buf, line_end + 1, ft_strchr(line_end + 1, '\0') - line_end);
	free(cache);
	return (new_line);
}

// Reads from a file looking for a linebreak or EOF
static char	*ft_read_line(int fd, char *buf, char **cache, char **line_end)
{
	ssize_t	read_bytes;

	*line_end = ft_strchr(*cache, '\n');
	while (!*line_end)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			if (read_bytes == 0 && **cache)
			{
				*line_end = ft_strchr(*cache, '\0') - 1;
				return (*line_end);
			}
			free(*cache);
			return (NULL);
		}
		*cache = ft_strjoin_gnl(buf, *cache, read_bytes);
		if (!*cache)
			return (NULL);
		*line_end = ft_strchr(*cache, '\n');
	}
	return (*line_end);
}

// Joins two strings together (cache with the readout from a buffer)
static char	*ft_strjoin_gnl(char *buf, char *cache, ssize_t read_bytes)
{
	size_t	cache_len;
	char	*new_cache;

	cache_len = 0;
	while (cache[cache_len] != '\0')
		cache_len++;
	new_cache = malloc(sizeof(char) * (cache_len + read_bytes + 1));
	if (!new_cache)
	{
		free(cache);
		return (NULL);
	}
	ft_memcpy(new_cache, cache, cache_len);
	ft_memcpy(new_cache + cache_len, buf, read_bytes);
	new_cache[cache_len + read_bytes] = '\0';
	free(cache);
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
