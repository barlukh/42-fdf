/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:44:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 11:50:42 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char	*ft_strdup(const char *s);

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
	size_t	start_i;
	size_t	ss_len;
	char	*ss;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	start_i = (size_t)start;
	if (start_i >= s_len)
		return (ft_strdup(""));
	else if (s_len - start_i >= len)
		ss_len = len;
	else
		ss_len = s_len - start_i;
	ss = malloc(sizeof(char) * (ss_len + 1));
	if (!ss)
		return (NULL);
	ft_memcpy(ss, s + start_i, ss_len);
	ss[ss_len] = '\0';
	return (ss);
}

// Duplicates a string using dynamic memory allocation
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
