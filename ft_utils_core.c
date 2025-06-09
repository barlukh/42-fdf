/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 16:00:20 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_init_window(mlx_t *mlx, t_sconfig *scfg)
{
	mlx_get_monitor_size(0, &scfg->monitor_w, &scfg->monitor_h);
	mlx_set_window_pos(mlx, (scfg->monitor_w - WIDTH) / 2,
		(scfg->monitor_h - HEIGHT) / 2);
	mlx_set_window_limit(mlx, scfg->monitor_w / 4, scfg->monitor_h / 4,
		scfg->monitor_w - (scfg->monitor_w / 10),
		scfg->monitor_h - (scfg->monitor_h / 10));
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}
