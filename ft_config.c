/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:15:21 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/14 19:04:26 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_bounding_box(t_config *cfg);

void	ft_config_window(t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->m_width, &cfg->m_height);
	mlx_set_window_pos(cfg->mlx, (cfg->m_width - WIDTH) / 2,
		(cfg->m_height - HEIGHT) / 1.2);
	mlx_set_window_limit(cfg->mlx, HEIGHT / 4, WIDTH / 4, HEIGHT, WIDTH);
	cfg->center_x = WIDTH / 2;
	cfg->center_y = HEIGHT / 2;
}

int	ft_config_matrix(t_config *cfg, void (*f)(t_config *))
{
	ft_fill_screen(cfg);
	f(cfg);
	ft_bounding_min_max(cfg);
	cfg->x_temp = fabs(cfg->x_max - cfg->x_min);
	cfg->y_temp = fabs(cfg->y_max - cfg->y_min);
	if (cfg->x_temp > cfg->y_temp)
		cfg->space = (WIDTH - WIDTH / 10) / cfg->x_temp;
	else
		cfg->space = (HEIGHT - HEIGHT / 10) / cfg->y_temp;
	if (cfg->space == 0)
	{
		mlx_errno = MLX_INVMAP;
		return (EXIT_FAILURE);
	}
	ft_bounding_box(cfg);
	return (EXIT_SUCCESS);
}

void	ft_bounding_min_max(t_config *cfg)
{
	cfg->x_min = INT32_MAX;
	cfg->x_max = INT32_MIN;
	cfg->y_min = INT32_MAX;
	cfg->y_max = INT32_MIN;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (cfg->pr[cfg->i].x > cfg->x_max)
			cfg->x_max = cfg->pr[cfg->i].x;
		if (cfg->pr[cfg->i].x < cfg->x_min)
			cfg->x_min = cfg->pr[cfg->i].x;
		if (cfg->pr[cfg->i].y > cfg->y_max)
			cfg->y_max = cfg->pr[cfg->i].y;
		if (cfg->pr[cfg->i].y < cfg->y_min)
			cfg->y_min = cfg->pr[cfg->i].y;
		cfg->i++;
	}
}

// Centers all points to the bounding box of the window with correct spacing.
static void	ft_bounding_box(t_config *cfg)
{
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (fabs(cfg->x_min) > fabs(cfg->x_max))
			cfg->pr[cfg->i].x = cfg->center_x + ((cfg->pr[cfg->i].x
						- cfg->x_min) - (cfg->x_temp / 2)) * cfg->space;
		else
			cfg->pr[cfg->i].x = cfg->center_x + ((cfg->pr[cfg->i].x
						- cfg->x_max) + (cfg->x_temp / 2)) * cfg->space;
		if (fabs(cfg->y_min) > fabs(cfg->y_max))
			cfg->pr[cfg->i].y = cfg->center_y + ((cfg->pr[cfg->i].y
						- cfg->y_min) - (cfg->y_temp / 2)) * cfg->space;
		else
			cfg->pr[cfg->i].y = cfg->center_y + ((cfg->pr[cfg->i].y
						- cfg->y_max) + (cfg->y_temp / 2)) * cfg->space;
		cfg->i++;
	}
}
