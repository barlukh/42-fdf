/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:54:05 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 19:11:24 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_point		*p;
	t_pconfig	pcfg;
	t_sconfig	scfg;

	if (ft_init_parse(argc, argv, &p, &pcfg) == EXIT_FAILURE)
		return (ft_exit_msg());
	// test
	int i = 0;
	while (i < (pcfg.line_size * pcfg.lst_size))
	{
		printf("[%d, %d, %d, %d] ", p[i].x, p[i].y, p[i].z, p[i].color);
		i++;
		if (i % pcfg.line_size == 0)
			printf("\n");
	}
	// ........................................
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		return (ft_exit_msg());
	ft_init_window(mlx, &scfg);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	return (ft_exit_terminate(mlx, p));
}
