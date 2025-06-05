/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/05 18:01:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(void)
{
	mlx_t		*mlx;
	t_config	cfg;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (ft_error(mlx));
	ft_config_window(mlx, &cfg);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
