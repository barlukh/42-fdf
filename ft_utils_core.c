/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/11 09:43:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_config_matrix(t_config *cfg)
{
	int	old_x;
	int	old_y;

	cfg->center_x = WIDTH / 2;
	cfg->center_y = HEIGHT / 2;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		old_x = cfg->p[cfg->i].x;
		old_y = cfg->p[cfg->i].y;
		cfg->p[cfg->i].x = (old_x + old_y) * cos(120);
		cfg->p[cfg->i].y = (old_y - old_x) * sin(120) - cfg->p[cfg->i].z;
		cfg->p[cfg->i].x = (cfg->center_x + (cfg->p[cfg->i].x * SPACE));
		cfg->p[cfg->i].y = cfg->center_y + (cfg->p[cfg->i].y * SPACE);
		cfg->i++;
	}
}

void	ft_config_window(mlx_t *mlx, t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->m_width, &cfg->m_height);
	mlx_set_window_pos(mlx, (cfg->m_width - WIDTH) / 2,
		(cfg->m_height - HEIGHT) / 2);
	mlx_set_window_limit(mlx, cfg->m_width / 4, cfg->m_height / 4,
		cfg->m_width - (cfg->m_width / 10),
		cfg->m_height - (cfg->m_height / 10));
	cfg->i = 0;
	while (cfg->i < (int)cfg->img->height)
	{
		cfg->j = 0;
		while (cfg->j < (int)cfg->img->width)
		{
			mlx_put_pixel(cfg->img, cfg->j, cfg->i, 0x000000FF);
			cfg->j++;
		}
		cfg->i++;
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}
