/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/11 08:57:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	mlx_t		*mlx;

	if (ft_parse(argc, argv, &cfg) == EXIT_FAILURE)
		return (ft_error_msg());
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (ft_error_msg());
	cfg.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!cfg.img)
		return (ft_error_img(mlx, &cfg));
	ft_config_window(mlx, &cfg);
	ft_config_matrix(&cfg);
	mlx_image_to_window(mlx, cfg.img, 0, 0);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop_hook(mlx, ft_draw, &cfg);
	mlx_loop(mlx);
	// .......................................
	int i = 0;
	while (i < (cfg.line_size * cfg.lst_size))
	{
		printf("[%.3f, %.3f, %.3f, %d] ", cfg.p[i].x, cfg.p[i].y, cfg.p[i].z, cfg.p[i].color);
		i++;
		if (i % cfg.line_size == 0)
		printf("\n");
	}
	// ........................................
	return (ft_exit_terminate(mlx, &cfg));
}
