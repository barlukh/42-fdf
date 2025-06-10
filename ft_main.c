/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 11:48:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_point		*p;

	
	if (ft_parse(argc, argv, &p, &cfg) == EXIT_FAILURE)
	return (ft_error_msg());
	// test
	int i = 0;
	while (i < (cfg.line_size * cfg.lst_size))
	{
		printf("[%d, %d, %d, %d] ", p[i].x, p[i].y, p[i].z, p[i].color);
		i++;
		if (i % cfg.line_size == 0)
		printf("\n");
	}
	// ........................................
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (ft_error_msg());
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (ft_error_img(mlx, p));
	ft_config_window(mlx, img, &cfg);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	return (ft_exit_terminate(mlx, img, p));
}
