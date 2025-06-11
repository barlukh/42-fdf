/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/11 17:12:45 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (ft_parse(argc, argv, &cfg) == EXIT_FAILURE)
		return (ft_error_msg());
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cfg.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!cfg.mlx)
		return (ft_error_msg());
	cfg.img = mlx_new_image(cfg.mlx, WIDTH, HEIGHT);
	if (!cfg.img)
		return (ft_error_img(&cfg));
	ft_config_window(&cfg);
	ft_config_matrix(&cfg);
	mlx_image_to_window(cfg.mlx, cfg.img, 0, 0);
	mlx_key_hook(cfg.mlx, ft_key_hook, &cfg);
	mlx_loop_hook(cfg.mlx, ft_draw, &cfg);
	mlx_loop(cfg.mlx);
	// .......................................
	//  int i = 0;
	//  while (i < (cfg.line_size * cfg.lst_size))
	//  {
	//  	printf("[%.3f, %.3f, %.3f, %d] ", cfg.p[i].x, cfg.p[i].y, cfg.p[i].z, cfg.p[i].color);
	//  	i++;
	//  	if (i % cfg.line_size == 0)
	//  	printf("\n");
	//  }
	// ........................................
	return (ft_exit_terminate(&cfg));
}
