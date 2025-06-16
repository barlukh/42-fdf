/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transformations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/16 11:10:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

static void	ft_scaling_in(t_config *cfg);
static void	ft_scaling_out(t_config *cfg);
static void	ft_translation(t_config *cfg, mlx_key_data_t keydata);
static void	ft_rotation(t_config *cfg, mlx_key_data_t keydata);

void	ft_key_hook(mlx_key_data_t k, void *param)
{
	t_config	*cfg;

	cfg = param;
	if (k.key == MLX_KEY_I && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		ft_scaling_in(cfg);
	else if (k.key == MLX_KEY_K && (k.action == MLX_PRESS
			|| k.action == MLX_REPEAT))
		ft_scaling_out(cfg);
	else if ((k.key == MLX_KEY_A && (k.action == MLX_PRESS
				|| k.action == MLX_REPEAT)) || (k.key == MLX_KEY_D
			&& (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		|| (k.key == MLX_KEY_W && (k.action == MLX_PRESS
				|| k.action == MLX_REPEAT)) || (k.key == MLX_KEY_S
			&& (k.action == MLX_PRESS || k.action == MLX_REPEAT)))
		ft_translation(cfg, k);
	else if ((k.key == MLX_KEY_J && (k.action == MLX_PRESS
				|| k.action == MLX_REPEAT)) || (k.key == MLX_KEY_L
			&& (k.action == MLX_PRESS || k.action == MLX_REPEAT)))
		ft_rotation(cfg, k);
	else if (k.key == MLX_KEY_C && (k.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_isometric);
	else if (k.key == MLX_KEY_V && (k.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_trimetric);
	else if (k.key == MLX_KEY_ESCAPE && k.action == MLX_PRESS)
		mlx_close_window(cfg->mlx);
}

// Zooms in with the center of the window being the zoom point.
static void	ft_scaling_in(t_config *cfg)
{
	int	limit_flag;

	limit_flag = FALSE;
	ft_fill_screen(cfg);
	ft_bounding_min_max(cfg);
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (fabs(cfg->x_min - cfg->x_max) > LIMIT_IN
			|| fabs(cfg->y_min - cfg->y_max) > LIMIT_IN)
			limit_flag = TRUE;
		cfg->i++;
	}
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size) && limit_flag == FALSE)
	{
		cfg->pr[cfg->i].x = cfg->center_x
			+ (cfg->pr[cfg->i].x - cfg->center_x) * ENLARGEMENT;
		cfg->pr[cfg->i].y = cfg->center_y
			+ (cfg->pr[cfg->i].y - cfg->center_y) * ENLARGEMENT;
		cfg->i++;
	}
}

// Zooms out with the center of the window being the zoom point.
static void	ft_scaling_out(t_config *cfg)
{
	int	limit_flag;

	limit_flag = FALSE;
	ft_fill_screen(cfg);
	ft_bounding_min_max(cfg);
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (fabs(cfg->x_min - cfg->x_max) < LIMIT_OUT
			|| fabs(cfg->y_min - cfg->y_max) < LIMIT_OUT)
			limit_flag = TRUE;
		cfg->i++;
	}
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size) && limit_flag == FALSE)
	{
		cfg->pr[cfg->i].x = cfg->center_x
			+ (cfg->pr[cfg->i].x - cfg->center_x) * CONTRACTION;
		cfg->pr[cfg->i].y = cfg->center_y
			+ (cfg->pr[cfg->i].y - cfg->center_y) * CONTRACTION;
		cfg->i++;
	}
}

// Moves the projection to the specified direction.
static void	ft_translation(t_config *cfg, mlx_key_data_t keydata)
{	
	ft_fill_screen(cfg);
	ft_bounding_min_max(cfg);
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		if (keydata.key == MLX_KEY_A && cfg->x_max > 0)
			cfg->pr[cfg->i].x = cfg->pr[cfg->i].x - TRANSLATION;
		else if (keydata.key == MLX_KEY_D && cfg->x_min < WIDTH)
			cfg->pr[cfg->i].x = cfg->pr[cfg->i].x + TRANSLATION;
		else if (keydata.key == MLX_KEY_W && cfg->y_max > 0)
			cfg->pr[cfg->i].y = cfg->pr[cfg->i].y - TRANSLATION;
		else if (keydata.key == MLX_KEY_S && cfg->y_min < HEIGHT)
			cfg->pr[cfg->i].y = cfg->pr[cfg->i].y + TRANSLATION;
		cfg->i++;
	}
}

// Rotates the projection around the center of the window.
static void	ft_rotation(t_config *cfg, mlx_key_data_t keydata)
{
	double	angle;
	double	c_x;
	double	c_y;

	ft_count_centroid(cfg, &c_x, &c_y);
	ft_fill_screen(cfg);
	if (keydata.key == MLX_KEY_L)
		angle = ROTATION_RIGHT;
	else
		angle = ROTATION_LEFT;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp = cfg->pr[cfg->i].x;
		cfg->y_temp = cfg->pr[cfg->i].y;
		cfg->pr[cfg->i].x = (cfg->x_temp - c_x) * cos(angle)
			- (cfg->y_temp - c_y) * sin(angle) + c_x;
		cfg->pr[cfg->i].y = (cfg->x_temp - c_x) * sin(angle)
			+ (cfg->y_temp - c_y) * cos(angle) + c_y;
		cfg->i++;
	}
}
