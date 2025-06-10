/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 16:57:48 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);

void	ft_draw(void *param)
{
	t_config	*cfg;

	cfg = param;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		mlx_put_pixel(cfg->img, cfg->p[cfg->i].x, cfg->p[cfg->i].y, 0xFFFFFF);
		if (cfg->i % cfg->line_size < cfg->line_size - 1
			&& cfg->i % cfg->lst_size < cfg->lst_size)
			ft_draw_line(cfg->img, cfg->p[cfg->i].x, cfg->p[cfg->i].y,
				cfg->p[cfg->i + 1].x, cfg->p[cfg->i + 1].y, cfg->p[cfg->i].color);
		if (cfg->i % cfg->lst_size < cfg->lst_size)
			ft_draw_line(cfg->img, cfg->p[cfg->i].x, cfg->p[cfg->i].y,
				cfg->p[(cfg->i + cfg->line_size) % cfg->line_size].x,
				cfg->p[(cfg->i + cfg->line_size) % cfg->line_size].y, cfg->p[cfg->i].color);
		cfg->i++;
	}
}

// Draws a line based on the Bresenham’s line algorithm
static void ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int dx = abs(x1 - x0), sx = (x0 < x1) ? 1 : -1;
	int dy = -abs(y1 - y0), sy = (y0 < y1) ? 1 : -1;
	int err = dx + dy, e2;

	while (1) {
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 > dy) { err += dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
	}
}
