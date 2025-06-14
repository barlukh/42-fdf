/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:02 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/14 15:44:53 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

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
