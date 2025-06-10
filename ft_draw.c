/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 18:53:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line(t_config *cfg, int x1, int y1);
static void	ft_draw_line_loop(t_config *cfg, int x1, int y1);

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
		{
			cfg->x0 = cfg->p[cfg->i].x;
			cfg->y0 = cfg->p[cfg->i].y;
			ft_draw_line(cfg, cfg->p[cfg->i + 1].x, cfg->p[cfg->i + 1].y);
		}
		if (cfg->i % cfg->lst_size < cfg->lst_size)
		{
			cfg->x0 = cfg->p[cfg->i].x;
			cfg->y0 = cfg->p[cfg->i].y;
			ft_draw_line(cfg,
				cfg->p[(cfg->i + cfg->line_size) % cfg->line_size].x,
				cfg->p[(cfg->i + cfg->line_size) % cfg->line_size].y);
		}
		cfg->i++;
	}
}

// Draws a line based on the Bresenham’s line algorithm (1 / 2)
static void	ft_draw_line(t_config *cfg, int x1, int y1)
{
	cfg->dx = fabs((float)x1 - (float)cfg->x0);
	cfg->dy = -fabs((float)y1 - (float)cfg->y0);
	cfg->sx = 1;
	if (cfg->x0 > x1)
		cfg->sx = -1;
	cfg->sy = 1;
	if (cfg->y0 > y1)
		cfg->sy = -1;
	cfg->err = cfg->dx + cfg->dy;
	ft_draw_line_loop(cfg, x1, y1);
}

// Draws a line based on the Bresenham’s line algorithm (2 / 2)
static void	ft_draw_line_loop(t_config *cfg, int x1, int y1)
{
	while (1)
	{
		mlx_put_pixel(cfg->img, cfg->x0, cfg->y0, cfg->p[cfg->i].color);
		if (cfg->x0 == x1 && cfg->y0 == y1)
			break ;
		cfg->e2 = 2 * cfg->err;
		if (cfg->e2 > cfg->dy)
		{
			cfg->err += cfg->dy;
			cfg->x0 += cfg->sx;
		}
		if (cfg->e2 < cfg->dx)
		{
			cfg->err += cfg->dx;
			cfg->y0 += cfg->sy;
		}
	}
}
