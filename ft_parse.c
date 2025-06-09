/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:34:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 19:36:55 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	ft_map_extract(t_pconfig *pcfg, t_list **lst);
static int	ft_map_sort(t_list **lst, t_point *p, t_pconfig *pcfg);
static int	ft_map_sort_matrix(char *point, t_point *p, t_pconfig *pcfg);
static int	ft_validate_arguments(int argc, char **argv, t_pconfig *pcfg);

int	ft_init_parse(int argc, char **argv, t_point **p, t_pconfig *pcfg)
{
	t_list	*lst;

	lst = NULL;
	pcfg->lst_size = 0;
	pcfg->line_size = 0;
	pcfg->i = 0;
	pcfg->j = 0;
	pcfg->k = 0;
	if (ft_validate_arguments(argc, argv, pcfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_map_extract(pcfg, &lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*p = malloc(pcfg->lst_size * pcfg->line_size * sizeof(t_point));
	if (!p || !*p)
	{
		mlx_errno = MLX_MEMFAIL;
		ft_lstclear(&lst);
		return (EXIT_FAILURE);
	}
	if (ft_map_sort(&lst, *p, pcfg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Links each row in the map file as a string to a linked list.
static int	ft_map_extract(t_pconfig *pcfg, t_list **lst)
{
	char	*line;
	t_list	*node;

	pcfg->comparison_size = INT32_MIN;
	line = ft_get_next_line(pcfg->fd);
	while (line != NULL)
	{
		pcfg->line_size = ft_word_count(line, ' ');
		if (pcfg->comparison_size == INT32_MIN)
			pcfg->comparison_size = pcfg->line_size;
		else if (pcfg->comparison_size != pcfg->line_size)
			return (ft_error_extract(line, lst, pcfg, MLX_INVMAP));
		node = ft_lstnew(line);
		if (!node)
			return (ft_error_extract(line, lst, pcfg, MLX_MEMFAIL));
		ft_lstadd_back(lst, node);
		line = ft_get_next_line(pcfg->fd);
	}
	pcfg->lst_size = ft_lstsize(*lst);
	close (pcfg->fd);
	return (EXIT_SUCCESS);
}

// Creates final struct for each point in the map.
static int	ft_map_sort(t_list **lst, t_point *p, t_pconfig *pcfg)
{
	t_list	*temp;
	char	**line;

	temp = *lst;
	while (temp != NULL)
	{
		line = ft_split((char *)temp->content, ' ');
		if (!line)
			return (ft_error_sort(lst, p));
		while (line[pcfg->i] != NULL)
		{
			if (ft_map_sort_matrix(line[pcfg->i], p, pcfg) == EXIT_FAILURE)
			{
				ft_free_split(line);
				return (ft_error_sort(lst, p));
			}
		}
		ft_free_split(line);
		pcfg->i = 0;
		pcfg->k++;
		temp = temp->next;
	}
	ft_lstclear(lst);
	return (EXIT_SUCCESS);
}

// Sorts X-axis, Y-axis, Z-axis and color attributes into a point matrix.
static int	ft_map_sort_matrix(char *point, t_point *p, t_pconfig *pcfg)
{
	p[pcfg->j].x = pcfg->j % pcfg->line_size;
	p[pcfg->j].y = pcfg->k;
	pcfg->c = ft_strchr(point, ',');
	if (pcfg->c == NULL)
	{
		p[pcfg->j].z = ft_atoi_base(point);
		p[pcfg->j].color = 0;
	}
	else
	{
		pcfg->split = ft_split(point, ',');
		if (pcfg->split == NULL)
			return (EXIT_FAILURE);
		p[pcfg->j].z = ft_atoi_base(pcfg->split[0]);
		p[pcfg->j].color = (uint32_t)ft_atoi_base(pcfg->split[1]);
		ft_free_split(pcfg->split);
	}
	pcfg->i++;
	pcfg->j++;
	return (EXIT_SUCCESS);
}

// Validates arguments passed from the command line.
static int	ft_validate_arguments(int argc, char **argv, t_pconfig *pcfg)
{
	if (argc != 2)
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	pcfg->c = ft_strchr(argv[1], '.');
	if (!pcfg->c || argv[1][0] == '.')
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	if ((*(pcfg->c + 1) != 'f' || *(pcfg->c + 2) != 'd'
			|| *(pcfg->c + 3) != 'f' || *(pcfg->c + 4) != '\0'))
	{
		mlx_errno = MLX_INVEXT;
		return (EXIT_FAILURE);
	}
	pcfg->fd = open(argv[1], O_RDONLY);
	if (pcfg->fd == -1)
	{
		mlx_errno = MLX_INVFILE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
