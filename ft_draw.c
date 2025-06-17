/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:57:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/17 09:00:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_draw_line_check(t_config *cfg);
static void	ft_draw_line(t_config *cfg, t_draw *var, int x1, int y1);
static void	ft_draw_line_loop(t_config *cfg, t_draw *var, int x1, int y1);
static void	ft_color_interpolation(t_config *cfg, t_draw *var, t_color *c);

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
		var.c_end = cfg->pr[cfg->i + cfg->line_size].color;
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
	t_color	c;

	while (1)
	{
		var->t = var->len++ / (var->dx + fabs(var->dy));
		if ((cfg->x0 > 0 && cfg->x0 < WIDTH)
			&& (cfg->y0 > 0 && cfg->y0 < HEIGHT) && cfg->c_flag == FALSE)
			ft_color_interpolation(cfg, var, &c);
		else if ((cfg->x0 > 0 && cfg->x0 < WIDTH)
			&& (cfg->y0 > 0 && cfg->y0 < HEIGHT))
			mlx_put_pixel(cfg->img, cfg->x0, cfg->y0, cfg->pr[cfg->i].color);
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

// Interpolates colors to create a smooth gradient.
static void	ft_color_interpolation(t_config *cfg, t_draw *var, t_color *c)
{
	c->gamma = 2.2;
	c->inv_gamma = 1.0 / c->gamma;
	c->r1 = (var->c_start >> 24) & 0xFF;
	c->g1 = (var->c_start >> 16) & 0xFF;
	c->b1 = (var->c_start >> 8) & 0xFF;
	c->a1 = (var->c_start) & 0xFF;
	c->r2 = (var->c_end >> 24) & 0xFF;
	c->g2 = (var->c_end >> 16) & 0xFF;
	c->b2 = (var->c_end >> 8) & 0xFF;
	c->a2 = (var->c_end) & 0xFF;
	c->r1_gamma = pow(c->r1 / 255.0, c->gamma);
	c->g1_gamma = pow(c->g1 / 255.0, c->gamma);
	c->b1_gamma = pow(c->b1 / 255.0, c->gamma);
	c->r2_gamma = pow(c->r2 / 255.0, c->gamma);
	c->g2_gamma = pow(c->g2 / 255.0, c->gamma);
	c->b2_gamma = pow(c->b2 / 255.0, c->gamma);
	c->r_interp = c->r1_gamma + (c->r2_gamma - c->r1_gamma) * var->t;
	c->g_interp = c->g1_gamma + (c->g2_gamma - c->g1_gamma) * var->t;
	c->b_interp = c->b1_gamma + (c->b2_gamma - c->b1_gamma) * var->t;
	c->r = (pow(c->r_interp, c->inv_gamma) * 255);
	c->g = (pow(c->g_interp, c->inv_gamma) * 255);
	c->b = (pow(c->b_interp, c->inv_gamma) * 255);
	c->a = c->a1 + ((c->a2 - c->a1) * var->t);
	c->graded_color = (c->r << 24) | (c->g << 16) | (c->b << 8) | c->a;
	mlx_put_pixel(cfg->img, cfg->x0, cfg->y0, c->graded_color);
}
