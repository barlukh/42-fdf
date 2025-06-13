/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 16:17:35 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line_check(t_config *cfg);
static void	ft_draw_line(t_config *cfg, int x1, int y1);
static void	ft_draw_line_loop(t_config *cfg, int x1, int y1);

void	ft_fill_screen(t_config *cfg)
{
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
		if ((cfg->pr[cfg->i].x > 0 && cfg->pr[cfg->i].x < WIDTH)
			&& (cfg->pr[cfg->i].y > 0 && cfg->pr[cfg->i].y < HEIGHT))
			mlx_put_pixel(cfg->img, cfg->pr[cfg->i].x, cfg->pr[cfg->i].y,
				cfg->pr[cfg->i].color);
		ft_draw_line_check(cfg);
		cfg->i++;
	}
}

// Checks for a validity of coordinates to draw a line between them.
static void	ft_draw_line_check(t_config *cfg)
{
	if (cfg->i % cfg->line_size < cfg->line_size - 1
		&& cfg->i % cfg->lst_size < cfg->lst_size)
	{
		cfg->x0 = cfg->pr[cfg->i].x;
		cfg->y0 = cfg->pr[cfg->i].y;
		ft_draw_line(cfg, cfg->pr[cfg->i + 1].x, cfg->pr[cfg->i + 1].y);
	}
	if (cfg->i < (cfg->line_size * (cfg->lst_size - 1)))
	{
		cfg->x0 = cfg->pr[cfg->i].x;
		cfg->y0 = cfg->pr[cfg->i].y;
		ft_draw_line(cfg,
			cfg->pr[(cfg->i + cfg->line_size)].x,
			cfg->pr[(cfg->i + cfg->line_size)].y);
	}
}

// Draws a line based on the Bresenham’s line algorithm.
static void	ft_draw_line(t_config *cfg, int x1, int y1)
{
	cfg->dx = fabs((float)x1 - cfg->x0);
	cfg->dy = -fabs((float)y1 - cfg->y0);
	cfg->sx = 1;
	if (cfg->x0 > x1)
		cfg->sx = -1;
	cfg->sy = 1;
	if (cfg->y0 > y1)
		cfg->sy = -1;
	cfg->err = cfg->dx + cfg->dy;
	ft_draw_line_loop(cfg, x1, y1);
}

// Main loop for the ft_draw_line() function.
static void	ft_draw_line_loop(t_config *cfg, int x1, int y1)
{
	while (1)
	{
		if ((cfg->x0 > 0 && cfg->x0 < WIDTH)
			&& (cfg->y0 > 0 && cfg->y0 < HEIGHT))
			mlx_put_pixel(cfg->img, cfg->x0, cfg->y0, cfg->pr[cfg->i].color);
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
