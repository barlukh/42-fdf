/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:17:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 11:34:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char	*ft_strdup(const char *s);

void	ft_putstr(const char *s)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	size_t	substr_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = (size_t)start;
	if (i >= s_len)
		return (ft_strdup(""));
	else if (s_len - i >= len)
		substr_len = len;
	else
		substr_len = s_len - i;
	substr = malloc(sizeof(char) * (substr_len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + i, substr_len);
	substr[substr_len] = '\0';
	return (substr);
}

// Duplicates a string using dynamic memory allocation.
static char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	s_len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (s_len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	ft_memcpy(ptr, s, s_len);
	ptr[s_len] = '\0';
	return (ptr);
}
