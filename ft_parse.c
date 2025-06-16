/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:34:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/16 12:17:37 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	ft_validate_arguments(int argc, char **argv, t_config *cfg);
static int	ft_map_extract(t_config *cfg, t_list **lst);
static int	ft_map_sort(t_list **lst, t_config *cfg);
static int	ft_map_sort_matrix(char *point, t_config *cfg);

int	ft_parse(int argc, char **argv, t_config *cfg)
{
	t_list	*lst;

	lst = NULL;
	cfg->lst_size = 0;
	cfg->line_size = 0;
	cfg->i = 0;
	cfg->j = 0;
	cfg->k = 0;
	if (ft_validate_arguments(argc, argv, cfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_map_extract(cfg, &lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cfg->p = malloc(cfg->lst_size * cfg->line_size * sizeof(t_point));
	if (!cfg->p)
	{
		mlx_errno = MLX_MEMFAIL;
		ft_lstclear(&lst);
		return (EXIT_FAILURE);
	}
	if (ft_map_sort(&lst, cfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Validates arguments passed from the command line.
static int	ft_validate_arguments(int argc, char **argv, t_config *cfg)
{
	if (argc != 2)
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	cfg->c = ft_strchr(argv[1], '.');
	if (!cfg->c || argv[1][0] == '.')
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	if ((*(cfg->c + 1) != 'f' || *(cfg->c + 2) != 'd'
			|| *(cfg->c + 3) != 'f' || *(cfg->c + 4) != '\0'))
	{
		mlx_errno = MLX_INVEXT;
		return (EXIT_FAILURE);
	}
	cfg->fd = open(argv[1], O_RDONLY);
	if (cfg->fd == -1)
	{
		mlx_errno = MLX_INVFILE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Links each row in the map file as a string to a linked list.
static int	ft_map_extract(t_config *cfg, t_list **lst)
{
	int		comparison_size;
	char	*line;
	t_list	*node;

	comparison_size = INT32_MIN;
	line = ft_get_next_line(cfg->fd);
	while (line != NULL)
	{
		cfg->line_size = ft_word_count(line, ' ');
		if (comparison_size == INT32_MIN)
			comparison_size = cfg->line_size;
		else if (comparison_size != cfg->line_size)
			return (ft_error_extract(line, lst, cfg, MLX_INVMAP));
		node = ft_lstnew(line);
		if (!node)
			return (ft_error_extract(line, lst, cfg, MLX_MEMFAIL));
		ft_lstadd_back(lst, node);
		line = ft_get_next_line(cfg->fd);
	}
	cfg->lst_size = ft_lstsize(*lst);
	close (cfg->fd);
	return (EXIT_SUCCESS);
}

// Creates final struct for each point in the map.
static int	ft_map_sort(t_list **lst, t_config *cfg)
{
	t_list	*temp;
	char	**line;

	cfg->c_flag = FALSE;
	temp = *lst;
	while (temp != NULL)
	{
		line = ft_split((char *)temp->content, ' ');
		if (!line)
			return (ft_error_sort(lst, cfg));
		while (line[cfg->i] != NULL)
		{
			if (ft_map_sort_matrix(line[cfg->i], cfg) == EXIT_FAILURE)
			{
				ft_free_split(line);
				return (ft_error_sort(lst, cfg));
			}
		}
		ft_free_split(line);
		cfg->i = 0;
		cfg->k++;
		temp = temp->next;
	}
	ft_lstclear(lst);
	return (EXIT_SUCCESS);
}

// Sorts X-axis, Y-axis, Z-axis and color attributes into a point matrix.
static int	ft_map_sort_matrix(char *point, t_config *cfg)
{
	char	**split;

	cfg->p[cfg->j].x = (cfg->j - (cfg->line_size / 2))
		- (cfg->k * cfg->line_size);
	cfg->p[cfg->j].y = cfg->k - (cfg->lst_size / 2);
	cfg->c = ft_strchr(point, ',');
	if (cfg->c == NULL)
	{
		cfg->p[cfg->j].z = ft_atoi_base(point);
		cfg->p[cfg->j].color = 0xFFFFFFFF;
	}
	else
	{
		split = ft_split(point, ',');
		if (split == NULL)
			return (EXIT_FAILURE);
		cfg->p[cfg->j].z = ft_atoi_base(split[0]);
		cfg->p[cfg->j].color = (uint32_t)ft_atoi_base(split[1]);
		cfg->p[cfg->j].color = cfg->p[cfg->j].color * 256 + 255;
		cfg->c_flag = TRUE;
		ft_free_split(split);
	}
	cfg->i++;
	cfg->j++;
	return (EXIT_SUCCESS);
}
