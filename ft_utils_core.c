/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 11:48:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_config_window(mlx_t *mlx,  mlx_image_t *img, t_config *cfg)
{
	uint32_t	x;
	uint32_t	y;

	mlx_get_monitor_size(0, &cfg->monitor_w, &cfg->monitor_h);
	mlx_set_window_pos(mlx, (cfg->monitor_w - WIDTH) / 2,
		(cfg->monitor_h - HEIGHT) / 2);
	mlx_set_window_limit(mlx, cfg->monitor_w / 4, cfg->monitor_h / 4,
		cfg->monitor_w - (cfg->monitor_w / 10),
		cfg->monitor_h - (cfg->monitor_h / 10));
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	mlx_put_pixel(img, WIDTH / 2, HEIGHT / 2, 0xFFFFFF);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}
