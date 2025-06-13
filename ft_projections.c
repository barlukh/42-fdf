/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 11:08:51 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_projection_isometric(t_config *cfg)
{
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp = cfg->p[cfg->i].x;
		cfg->y_temp = cfg->p[cfg->i].y;
		cfg->p[cfg->i].x = (cfg->x_temp - cfg->y_temp) / sqrt(2);
		cfg->p[cfg->i].y = (cfg->x_temp + cfg->y_temp - 2
			* cfg->p[cfg->i].z) / sqrt(6);
		if (cfg->p[cfg->i].x > cfg->x_max)
			cfg->x_max = cfg->p[cfg->i].x;
		if (cfg->p[cfg->i].x < cfg->x_min)
			cfg->x_min = cfg->p[cfg->i].x;
		if (cfg->p[cfg->i].y > cfg->y_max)
			cfg->y_max = cfg->p[cfg->i].y;
		if (cfg->p[cfg->i].y < cfg->y_min)
			cfg->y_min = cfg->p[cfg->i].y;
		cfg->i++;
	}
}

void	ft_projection_dimetric(t_config *cfg)
{
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp = cfg->p[cfg->i].x;
		cfg->y_temp = cfg->p[cfg->i].y;
		cfg->p[cfg->i].x = (cfg->x_temp + cfg->y_temp) * cos(120);
		cfg->p[cfg->i].y = (cfg->y_temp - cfg->x_temp) * sin(120) - cfg->p[cfg->i].z;
		if (cfg->p[cfg->i].x > cfg->x_max)
			cfg->x_max = cfg->p[cfg->i].x;
		if (cfg->p[cfg->i].x < cfg->x_min)
			cfg->x_min = cfg->p[cfg->i].x;
		if (cfg->p[cfg->i].y > cfg->y_max)
			cfg->y_max = cfg->p[cfg->i].y;
		if (cfg->p[cfg->i].y < cfg->y_min)
			cfg->y_min = cfg->p[cfg->i].y;
		cfg->i++;
	}
}
