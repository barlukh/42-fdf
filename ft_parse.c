/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:34:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/08 11:18:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	ft_validate_arguments(int argc, char **argv);
static int	ft_validate_file(int *fd, char **argv);
static int	ft_validate_map(int fd, t_list **lst);

int	ft_init_parse(int argc, char **argv)
{
	int		fd;
	t_list	*lst;

	lst = NULL;
	if (ft_validate_arguments(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_validate_file(&fd, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_validate_map(fd, &lst) == EXIT_FAILURE)
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

static int	ft_validate_file(int *fd, char **argv)
{
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
	{
		mlx_errno = MLX_INVFILE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_validate_map(int fd, t_list **lst)
{
	char	*line;
	t_list	*node;

	while (1)
	{
		line = ft_get_next_line(fd);
		if (line == NULL)
			break ;
		node = ft_lstnew(line);
		ft_lstadd_back(lst, node);
	}
	ft_lstclear(lst);
	close (fd);
	return (EXIT_SUCCESS);
}
