/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:27:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 13:15:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_exit_msg(void)
{
	ft_putstr(mlx_strerror(mlx_errno));
	return (mlx_errno);
}

int	ft_exit_term(mlx_t *mlx, t_point *pt)
{
	ft_putstr(mlx_strerror(mlx_errno));
	free(pt);
	mlx_terminate(mlx);
	return (mlx_errno);
}

int	ft_free_extract(char *line, t_list **lst, int fd, int error_flag)
{
	mlx_errno = error_flag;
	free(line);
	ft_lstclear(lst);
	close (fd);
	return (EXIT_FAILURE);
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
