/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:38:11 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 11:46:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static char		**ft_allocate_array(char const *s, char c, char **arr);
static void		ft_free_array(char **arr, size_t i);
static size_t	ft_word_count(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**arr;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_allocate_array(s, c, arr);
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	return (arr);
}

// Allocates each single word into its array
static char	**ft_allocate_array(char const *s, char c, char **arr)
{
	size_t	word_len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = ft_strchr(s, c) - s;
			else
				word_len = ft_strlen(s);
			arr[i] = ft_substr(s, 0, word_len);
			if (!arr[i])
			{
				ft_free_array(arr, i);
				return (NULL);
			}
			s += word_len;
			i++;
		}
	}
	return (arr);
}

// Frees all arrays
static void	ft_free_array(char **arr, size_t i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	free(arr);
}

// Counts how many words to split the string into
static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}
