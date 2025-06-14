/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transformations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/14 19:14:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

static void	ft_translation(t_config *cfg, mlx_key_data_t keydata);
static void	ft_scaling(t_config *cfg, mlx_key_data_t keydata);
static void	ft_rotation(t_config *cfg, mlx_key_data_t keydata);

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_config	*cfg;

	cfg = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cfg->mlx);
	else if ((keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT)) || (keydata.key == MLX_KEY_D
			&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		|| (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT)) || (keydata.key == MLX_KEY_S
			&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		ft_translation(cfg, keydata);
	else if ((keydata.key == MLX_KEY_I && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT)) || (keydata.key == MLX_KEY_K
			&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		ft_scaling(cfg, keydata);
	else if ((keydata.key == MLX_KEY_J && (keydata.action == MLX_PRESS
				|| keydata.action == MLX_REPEAT)) || (keydata.key == MLX_KEY_L
			&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		ft_rotation(cfg, keydata);
	else if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_isometric);
	else if (keydata.key == MLX_KEY_V && (keydata.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_trimetric);
}

// Moves the projection to the specified direction.
static void	ft_translation(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (keydata.key == MLX_KEY_A)
			cfg->pr[cfg->i].x = cfg->pr[cfg->i].x - TRANSLATION;
		else if (keydata.key == MLX_KEY_D)
			cfg->pr[cfg->i].x = cfg->pr[cfg->i].x + TRANSLATION;
		else if (keydata.key == MLX_KEY_W)
			cfg->pr[cfg->i].y = cfg->pr[cfg->i].y - TRANSLATION;
		else
			cfg->pr[cfg->i].y = cfg->pr[cfg->i].y + TRANSLATION;
		cfg->i++;
	}
}

// Zooms in or out with the center of the window being the zoom point.
static void	ft_scaling(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (keydata.key == MLX_KEY_I)
		{
			cfg->pr[cfg->i].x = cfg->center_x
				+ (cfg->pr[cfg->i].x - cfg->center_x) * ENLARGEMENT;
			cfg->pr[cfg->i].y = cfg->center_y
				+ (cfg->pr[cfg->i].y - cfg->center_y) * ENLARGEMENT;
		}
		else
		{
			cfg->pr[cfg->i].x = cfg->center_x
				+ (cfg->pr[cfg->i].x - cfg->center_x) * CONTRACTION;
			cfg->pr[cfg->i].y = cfg->center_y
				+ (cfg->pr[cfg->i].y - cfg->center_y) * CONTRACTION;
		}
		cfg->i++;
	}
}

// Rotates the projection around the center of the window.
static void	ft_rotation(t_config *cfg, mlx_key_data_t keydata)
{
	double	angle;

	ft_fill_screen(cfg);
	ft_bounding_min_max(cfg);
	if (keydata.key == MLX_KEY_L)
		angle = ROTATION_RIGHT;
	else
		angle = ROTATION_LEFT;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp = cfg->pr[cfg->i].x;
		cfg->y_temp = cfg->pr[cfg->i].y;
		cfg->pr[cfg->i].x = (cfg->x_temp - cfg->center_x) * cos(angle)
			- (cfg->y_temp - cfg->center_y) * sin(angle) + cfg->center_x;
		cfg->pr[cfg->i].y = (cfg->x_temp - cfg->center_x) * sin(angle)
			+ (cfg->y_temp - cfg->center_y) * cos(angle) + cfg->center_y;
		cfg->i++;
	}
}
