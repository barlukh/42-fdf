/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/17 07:13:17 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line_check(t_config *cfg);
static void	ft_draw_line(t_config *cfg, t_draw *var, int x1, int y1);
static void	ft_draw_line_loop(t_config *cfg, t_draw *var, int x1, int y1);
static void	ft_color_grading(t_config *cfg, t_draw *var);

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
	t_draw	var;

	if (cfg->i % cfg->line_size < cfg->line_size - 1
		&& cfg->i % cfg->lst_size < cfg->lst_size)
	{
		cfg->x0 = cfg->pr[cfg->i].x;
		cfg->y0 = cfg->pr[cfg->i].y;
		var.c_start = cfg->pr[cfg->i].color;
		var.c_end = cfg->pr[cfg->i + 1].color;
		ft_draw_line(cfg, &var, cfg->pr[cfg->i + 1].x, cfg->pr[cfg->i + 1].y);
	}
	if (cfg->i < (cfg->line_size * (cfg->lst_size - 1)))
	{
		cfg->x0 = cfg->pr[cfg->i].x;
		cfg->y0 = cfg->pr[cfg->i].y;
		var.c_start = cfg->pr[cfg->i].color;
		var.c_end = cfg->pr[cfg->i + 1].color;
		ft_draw_line(cfg, &var,
			cfg->pr[(cfg->i + cfg->line_size)].x,
			cfg->pr[(cfg->i + cfg->line_size)].y);
	}
}

// Draws a line based on the Bresenham’s line algorithm.
static void	ft_draw_line(t_config *cfg, t_draw *var, int x1, int y1)
{
	var->len = 0;
	var->dx = fabs((float)x1 - cfg->x0);
	var->dy = -fabs((float)y1 - cfg->y0);
	var->sx = 1;
	if (cfg->x0 > x1)
		var->sx = -1;
	var->sy = 1;
	if (cfg->y0 > y1)
		var->sy = -1;
	var->err = var->dx + var->dy;
	ft_draw_line_loop(cfg, var, x1, y1);
}

// Main loop for the ft_draw_line() function.
static void	ft_draw_line_loop(t_config *cfg, t_draw *var, int x1, int y1)
{
	while (1)
	{
		var->len++;
		var->t = var->len / (var->dx + fabs(var->dy));
		ft_color_grading(cfg, var);
		if (cfg->x0 == x1 && cfg->y0 == y1)
			break ;
		var->e2 = 2 * var->err;
		if (var->e2 > var->dy)
		{
			var->err += var->dy;
			cfg->x0 += var->sx;
		}
		if (var->e2 < var->dx)
		{
			var->err += var->dx;
			cfg->y0 += var->sy;
		}
	}
}

static void	ft_color_grading(t_config *cfg, t_draw *var)
{
	t_color	c;

	c.r1 = (var->c_start >> 24) & 0xFF;
	c.g1 = (var->c_start >> 16) & 0xFF;
	c.b1 = (var->c_start >> 8) & 0xFF;
	c.a1 = (var->c_start) & 0xFF;
	c.r2 = (var->c_end >> 24) & 0xFF;
	c.g2 = (var->c_end >> 16) & 0xFF;
	c.b2 = (var->c_end >> 8) & 0xFF;
	c.a2 = (var->c_end) & 0xFF;
	c.r = c.r1 + ((c.r2 - c.r1) * var->t);
	c.g = c.g1 + ((c.g2 - c.g1) * var->t);
	c.b = c.b1 + ((c.b2 - c.b1) * var->t);
	c.a = c.a1 + ((c.a2 - c.a1) * var->t);
	c.graded_color = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
	if ((cfg->x0 > 0 && cfg->x0 < WIDTH)
		&& (cfg->y0 > 0 && cfg->y0 < HEIGHT))
		mlx_put_pixel(cfg->img, cfg->x0, cfg->y0, c.graded_color);
}
