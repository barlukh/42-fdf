/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 07:32:35 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_move_camera_x(t_config *cfg, mlx_key_data_t keydata);
static void	ft_move_camera_y(t_config *cfg, mlx_key_data_t keydata);
static void	ft_zoom(t_config *cfg, mlx_key_data_t keydata);

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_config	*cfg;

	cfg = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cfg->mlx);
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_camera_x(cfg, keydata);
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_camera_x(cfg, keydata);
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_camera_y(cfg, keydata);
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_move_camera_y(cfg, keydata);
	if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_zoom(cfg, keydata);
	if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_zoom(cfg, keydata);
}

static void	ft_move_camera_x(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_D)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->p[cfg->i].x - SPEED;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_A)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->p[cfg->i].x + SPEED;
			cfg->i++;
		}
	}
}

static void	ft_move_camera_y(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_S)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].y = cfg->p[cfg->i].y - SPEED;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_W)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].y = cfg->p[cfg->i].y + SPEED;
			cfg->i++;
		}
	}
}

static void	ft_zoom(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_UP)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->center_x
				+ (cfg->p[cfg->i].x - cfg->center_x) * 1.2;
			cfg->p[cfg->i].y = cfg->center_y
				+ (cfg->p[cfg->i].y - cfg->center_y) * 1.2;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_DOWN)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->center_x
				+ (cfg->p[cfg->i].x - cfg->center_x) * 0.8;
			cfg->p[cfg->i].y = cfg->center_y
				+ (cfg->p[cfg->i].y - cfg->center_y) * 0.8;
			cfg->i++;
		}
	}
}
