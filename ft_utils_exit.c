/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:27:26 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 07:46:49 by bgazur           ###   ########.fr       */
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

int	ft_error_msg(void)
{
	ft_putstr(mlx_strerror(mlx_errno));
	return (mlx_errno);
}

int	ft_error_sort(t_list **lst, t_config *cfg)
{
	mlx_errno = MLX_MEMFAIL;
	ft_lstclear(lst);
	free(cfg->p);
	return (EXIT_FAILURE);
}

int	ft_error_img(t_config *cfg)
{
	mlx_errno = MLX_MEMFAIL;
	ft_putstr(mlx_strerror(mlx_errno));
	free(cfg->p);
	mlx_terminate(cfg->mlx);
	return (mlx_errno);
}

int	ft_exit_terminate(t_config *cfg)
{
	ft_putstr(mlx_strerror(mlx_errno));
	free(cfg->p);
	mlx_delete_image(cfg->mlx, cfg->img);
	mlx_terminate(cfg->mlx);
	return (mlx_errno);
}
