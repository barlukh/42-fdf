/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:34:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 16:59:25 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	ft_validate_arguments(int argc, char **argv);
static int	ft_validate_file(char **argv);

int	ft_parse_input(int argc, char **argv)
{
	if (ft_validate_arguments(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_validate_file(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_validate_arguments(int argc, char **argv)
{
	char	*dot;

	if (argc != 2)
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	dot = ft_strchr(argv[1], '.');
	if (!dot || argv[1][0] == '.')
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	if ((*(dot + 1) != 'f' || *(dot + 2) != 'd'
		|| *(dot + 3) != 'f' || *(dot + 4) != '\0'))
	{
		mlx_errno = MLX_INVEXT;	
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_validate_file(char **argv)
{
	
}