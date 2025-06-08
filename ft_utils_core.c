/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:06:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/08 14:27:55 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	ft_putstr(const char *s);

int	ft_exit_msg(void)
{
	ft_putstr(mlx_strerror(mlx_errno));
	return (mlx_errno);
}

int	ft_exit_term(mlx_t *mlx)
{
	ft_putstr(mlx_strerror(mlx_errno));
	mlx_terminate(mlx);
	return (mlx_errno);
}

void	ft_init_window(mlx_t *mlx, t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->monitor_width, &cfg->monitor_height);
	mlx_set_window_pos(mlx, (cfg->monitor_width - WIDTH) / 2,
		(cfg->monitor_height - HEIGHT) / 2);
	mlx_set_window_limit(mlx, cfg->monitor_width / 4, cfg->monitor_height / 4,
		cfg->monitor_width - (cfg->monitor_width / 10),
		cfg->monitor_height - (cfg->monitor_height / 10));
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

// Writes a string into the standard output followed by a newline character.
static void	ft_putstr(const char *s)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
