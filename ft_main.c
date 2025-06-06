/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/07 19:18:23 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_config	cfg;

	mlx = NULL;
	if (ft_init_parse(argc, argv) == EXIT_FAILURE)
		return (ft_exit(mlx));
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (ft_exit(mlx));
	ft_init_window(mlx, &cfg);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	return (ft_exit(mlx));
}
