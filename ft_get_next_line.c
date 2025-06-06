/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:17:16 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 11:37:37 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

char	*ft_get_next_line(int fd)
{
	static char	*buf;
	t_struct	var;

	if (!buf)
	{
		buf = malloc(BUFFER_SIZE);
		if (!buf)
			return (NULL);
		buf[0] = '\0';
	}
	var.cache = ft_substr(&buf, ft_strchr(buf, '\0') - buf);
	if (!var.cache)
		return (NULL);
	if (ft_line_read(fd, &buf, &var) == NULL)
		return (NULL);
	var.new_line = ft_substr(&var.cache, var.br - var.cache + 1);
	if (!var.new_line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	ft_memcpy(buf, var.br + 1, ft_strchr(var.br + 1, '\0') - var.br);
	free(var.cache);
	return (var.new_line);
}
