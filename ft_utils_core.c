/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 15:12:43 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);

void	ft_config_matrix(t_config *cfg)
{
	cfg->center_x = WIDTH / 2;
	cfg->center_y = HEIGHT / 2;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->p[cfg->i].x = cfg->center_x + (cfg->p[cfg->i].x * SPACE);
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

void	ft_draw(void *param)
{
	t_config	*cfg;

	cfg = param;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		mlx_put_pixel(cfg->img, cfg->p[cfg->i].x, cfg->p[cfg->i].y, 0xFFFFFF);
		if (cfg->i % cfg->line_size < cfg->line_size / 2
			&& cfg->i % cfg->lst_size < cfg->lst_size / 2)
				ft_draw_line(cfg->img, cfg->p[cfg->i].x, cfg->p[cfg->i].y,
					cfg->p[cfg->i + 1].x, cfg->p[cfg->i + 1].y, 0xFFFFFF);
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

#include <stdlib.h>

static void ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0), sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0), sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        if (x0 >= 0 && x0 < (int)img->width && y0 >= 0 && y0 < (int)img->height) {
            mlx_put_pixel(img, x0, y0, color);  // Place pixel
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}
