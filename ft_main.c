/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/16 12:08:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (ft_parse(argc, argv, &cfg) == EXIT_FAILURE)
	{
		ft_putstr(mlx_strerror(mlx_errno));
		return (mlx_errno);
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cfg.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!cfg.mlx)
		return (ft_error_init(&cfg));
	cfg.img = mlx_new_image(cfg.mlx, WIDTH, HEIGHT);
	if (!cfg.img)
		return (ft_error_img(&cfg));
	ft_config_window(&cfg);
	cfg.pr = malloc(cfg.lst_size * cfg.line_size * sizeof(t_point));
	if (!cfg.pr)
		return (ft_error_pr(&cfg));
	if (ft_config_matrix(&cfg, ft_projection_isometric) == EXIT_FAILURE)
		return (ft_exit_terminate(&cfg));
	mlx_image_to_window(cfg.mlx, cfg.img, 0, 0);
	mlx_key_hook(cfg.mlx, ft_key_hook, &cfg);
	mlx_loop_hook(cfg.mlx, ft_draw, &cfg);
	mlx_loop(cfg.mlx);
	return (ft_exit_terminate(&cfg));
}
