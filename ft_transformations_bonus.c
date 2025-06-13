/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transformations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 11:14:03 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_translation_x(t_config *cfg, mlx_key_data_t keydata);
static void	ft_translation_y(t_config *cfg, mlx_key_data_t keydata);
static void	ft_scaling(t_config *cfg, mlx_key_data_t keydata);

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_config	*cfg;

	cfg = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cfg->mlx);
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_translation_x(cfg, keydata);
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_translation_x(cfg, keydata);
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_translation_y(cfg, keydata);
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_translation_y(cfg, keydata);
	if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_scaling(cfg, keydata);
	if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_scaling(cfg, keydata);
	if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_isometric);
	if (keydata.key == MLX_KEY_V && (keydata.action == MLX_PRESS))
		ft_config_matrix(cfg, ft_projection_dimetric);
}

static void	ft_translation_x(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_D)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->p[cfg->i].x - TRANSLATION;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_A)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->p[cfg->i].x + TRANSLATION;
			cfg->i++;
		}
	}
}

static void	ft_translation_y(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_S)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].y = cfg->p[cfg->i].y - TRANSLATION;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_W)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].y = cfg->p[cfg->i].y + TRANSLATION;
			cfg->i++;
		}
	}
}

static void	ft_scaling(t_config *cfg, mlx_key_data_t keydata)
{
	ft_fill_screen(cfg);
	cfg->i = 0;
	if (keydata.key == MLX_KEY_UP)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->center_x
				+ (cfg->p[cfg->i].x - cfg->center_x) * ENLARGEMENT;
			cfg->p[cfg->i].y = cfg->center_y
				+ (cfg->p[cfg->i].y - cfg->center_y) * ENLARGEMENT;
			cfg->i++;
		}
	}
	if (keydata.key == MLX_KEY_DOWN)
	{
		while (cfg->i < (cfg->line_size * cfg->lst_size))
		{
			cfg->p[cfg->i].x = cfg->center_x
				+ (cfg->p[cfg->i].x - cfg->center_x) * CONTRACTION;
			cfg->p[cfg->i].y = cfg->center_y
				+ (cfg->p[cfg->i].y - cfg->center_y) * CONTRACTION;
			cfg->i++;
		}
	}
}
