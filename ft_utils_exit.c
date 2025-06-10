/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:27:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 10:03:26 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_error_extract(char *line, t_list **lst, t_config *cfg, int flag)
{
	mlx_errno = flag;
	free(line);
	ft_lstclear(lst);
	close (cfg->fd);
	return (EXIT_FAILURE);
}

int ft_error_img(mlx_t *mlx, t_point *p)
{
	mlx_errno = MLX_MEMFAIL;
	ft_putstr(mlx_strerror(mlx_errno));
	free(p);
	mlx_terminate(mlx);
	return (mlx_errno);
}

int	ft_error_msg(void)
{
	ft_putstr(mlx_strerror(mlx_errno));
	return (mlx_errno);
}

int	ft_error_sort(t_list **lst, t_point *p)
{
	mlx_errno = MLX_MEMFAIL;
	ft_lstclear(lst);
	free(p);
	return (EXIT_FAILURE);
}

int	ft_exit_terminate(mlx_t *mlx, mlx_image_t *img, t_point *p)
{
	ft_putstr(mlx_strerror(mlx_errno));
	free(p);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (mlx_errno);
}
