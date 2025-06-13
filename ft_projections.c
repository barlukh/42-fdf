/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/13 10:10:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	ft_projection_isometric(t_config *cfg)
{
	cfg->x_temp = cfg->p[cfg->i].x;
	cfg->y_temp = cfg->p[cfg->i].y;
	cfg->p[cfg->i].x = (cfg->x_temp - cfg->y_temp) / sqrt(2);
	cfg->p[cfg->i].y = (cfg->x_temp + cfg->y_temp - 2
		* cfg->p[cfg->i].z) / sqrt(6);
}
