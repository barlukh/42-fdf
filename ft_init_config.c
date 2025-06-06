/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/05 17:31:22 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_config_window(mlx_t *mlx, t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->monitor_width, &cfg->monitor_height);
	mlx_set_window_pos(mlx, (cfg->monitor_width - WIDTH) / 2,
		(cfg->monitor_height - HEIGHT) / 2);
	mlx_set_window_limit(mlx, cfg->monitor_width / 4, cfg->monitor_height / 4,
		cfg->monitor_width - (cfg->monitor_width / 10),
		cfg->monitor_height - (cfg->monitor_height / 10));
}

int	ft_error(mlx_t *mlx)
{
	ft_printf("%s\n", mlx_strerror(mlx_errno));
	mlx_terminate(mlx);
	return (mlx_errno);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}
