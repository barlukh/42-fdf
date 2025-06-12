/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:15:21 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/12 17:31:21 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_boundig_box_draw(t_config *cfg);
static void	ft_bounding_min_max(t_config *cfg);

void	ft_config_matrix(t_config *cfg)
{
	cfg->x_max = 0;
	cfg->x_min = 0;
	cfg->y_max = 0;
	cfg->y_min = 0;
	cfg->center_x = WIDTH / 2;
	cfg->center_y = HEIGHT / 2;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp = cfg->p[cfg->i].x;
		cfg->y_temp = cfg->p[cfg->i].y;
		cfg->p[cfg->i].x = (cfg->x_temp + cfg->y_temp) * cos(120);
		cfg->p[cfg->i].y = (cfg->y_temp - cfg->x_temp) * sin(120) - cfg->p[cfg->i].z;
		ft_bounding_min_max(cfg);
		cfg->i++;
	}
	cfg->x_temp = fabs(cfg->x_max - cfg->x_min);
	cfg->y_temp = fabs(cfg->y_max - cfg->y_min);
	ft_boundig_box_draw(cfg);
}

void	ft_config_window(t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->m_width, &cfg->m_height);
	mlx_set_window_pos(cfg->mlx, (cfg->m_width - WIDTH) / 2,
		(cfg->m_height - HEIGHT) / 2);
	mlx_set_window_limit(cfg->mlx, cfg->m_width / 4, cfg->m_height / 4,
		cfg->m_width - (cfg->m_width / 10),
		cfg->m_height - (cfg->m_height / 10));
	ft_fill_screen(cfg);
}

static void	ft_boundig_box_draw(t_config *cfg)
{
	if (cfg->x_temp > cfg->y_temp)
	{
		cfg->xy_bounder = cfg->x_temp;
		cfg->space = (WIDTH - WIDTH / 10) / cfg->xy_bounder;
	}
	else
	{
		cfg->xy_bounder = cfg->y_temp;
		cfg->space = (HEIGHT - HEIGHT / 10) / cfg->xy_bounder;
	}
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->p[cfg->i].x = cfg->center_x + (cfg->p[cfg->i].x * cfg->space);
		if (fabs(cfg->y_min) > fabs(cfg->y_max))
		{
			cfg->p[cfg->i].y = cfg->center_y + fabs(2 * cfg->y_min)
				+ (cfg->p[cfg->i].y * cfg->space);
		}
		else
			cfg->p[cfg->i].y = cfg->center_y + fabs(2 * cfg->y_max)
				+ (cfg->p[cfg->i].y * cfg->space);
		cfg->i++;
	}
}

static void	ft_bounding_min_max(t_config *cfg)
{
	if (cfg->p[cfg->i].x > cfg->x_max)
		cfg->x_max = cfg->p[cfg->i].x;
	if (cfg->p[cfg->i].x < cfg->x_min)
		cfg->x_min = cfg->p[cfg->i].x;
	if (cfg->p[cfg->i].y > cfg->y_max)
		cfg->y_max = cfg->p[cfg->i].y;
	if (cfg->p[cfg->i].y < cfg->y_min)
		cfg->y_min = cfg->p[cfg->i].y;
}
