/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:27:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 16:26:24 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_error_extract(char *line, t_list **lst, t_pconfig *pcfg, int flag)
{
	mlx_errno = flag;
	free(line);
	ft_lstclear(lst);
	close (pcfg->fd);
	return (EXIT_FAILURE);
}

int	ft_error_sort(t_list **lst, t_point *p)
{
	mlx_errno = MLX_MEMFAIL;
	ft_lstclear(lst);
	free(p);
	return (EXIT_FAILURE);
}

int	ft_exit_msg(void)
{
	ft_putstr(mlx_strerror(mlx_errno));
	return (mlx_errno);
}

int	ft_exit_terminate(mlx_t *mlx, t_point *p)
{
	ft_putstr(mlx_strerror(mlx_errno));
	free(p);
	mlx_terminate(mlx);
	return (mlx_errno);
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
