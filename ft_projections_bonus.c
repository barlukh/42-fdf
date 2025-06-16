/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:29:07 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/16 11:09:21 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf_bonus.h"

void	ft_projection_isometric(t_config *cfg)
{
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->pr[cfg->i] = cfg->p[cfg->i];
		cfg->x_temp = cfg->pr[cfg->i].x;
		cfg->y_temp = cfg->pr[cfg->i].y;
		cfg->pr[cfg->i].x = (cfg->x_temp - cfg->y_temp) / sqrt(2);
		cfg->pr[cfg->i].y = (cfg->x_temp + cfg->y_temp - 2
				* cfg->pr[cfg->i].z) / sqrt(6);
		cfg->i++;
	}
}

void	ft_projection_trimetric(t_config *cfg)
{
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->pr[cfg->i] = cfg->p[cfg->i];
		cfg->x_temp = cfg->pr[cfg->i].x;
		cfg->y_temp = cfg->pr[cfg->i].y;
		cfg->pr[cfg->i].x = (cfg->x_temp - cfg->y_temp) / sqrt(3);
		cfg->pr[cfg->i].y = (cfg->x_temp * 0.8 + cfg->y_temp * 1.2
				- cfg->pr[cfg->i].z * 1.5) / sqrt(7);
		cfg->i++;
	}
}

void	ft_count_centroid(t_config *cfg, double *c_x, double *c_y)
{
	cfg->i = 0;
	cfg->x_temp = 0;
	cfg->y_temp = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		cfg->x_temp += cfg->pr[cfg->i].x;
		cfg->y_temp += cfg->pr[cfg->i].y;
		cfg->i++;
	}
	*c_x = cfg->x_temp / (cfg->line_size * cfg->lst_size);
	*c_y = cfg->y_temp / (cfg->line_size * cfg->lst_size);
}
