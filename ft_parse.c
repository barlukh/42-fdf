/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:34:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/09 17:13:19 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	ft_map_extract(t_pconfig *pcfg, t_list **lst);
static int	ft_map_sort(t_list **lst, t_point *p, t_pconfig *pcfg);
static int	ft_validate_arguments(int argc, char **argv, t_pconfig *pcfg);

int	ft_init_parse(int argc, char **argv, t_point **p, t_pconfig *pcfg)
{
	t_list	*lst;

	lst = NULL;
	pcfg->lst_size = 0;
	pcfg->line_size = 0;
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
	size_t	i;
	size_t	j;
	size_t	k;
	char	**line;

	temp = *lst;
	i = 0;
	j = 0;
	k = 0;
	while (temp != NULL)
	{
		line = ft_split((char *)temp->content, ' ');
		if (!line)
			return (ft_error_sort(lst, p));
		while (line[i] != NULL)
		{
			p[j].x = j % pcfg->line_size;
			p[j].y = k;
			p[j].z = ft_atoi(line[i]);
			p[j].color = 0;
			i++;
			j++;
		}
		ft_free_split(line);
		i = 0;
		k++;
		temp = temp->next;
	}
	ft_lstclear(lst);
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
	pcfg->dot = ft_strchr(argv[1], '.');
	if (!pcfg->dot || argv[1][0] == '.')
	{
		mlx_errno = MLX_INVARGS;
		return (EXIT_FAILURE);
	}
	if ((*(pcfg->dot + 1) != 'f' || *(pcfg->dot + 2) != 'd'
			|| *(pcfg->dot + 3) != 'f' || *(pcfg->dot + 4) != '\0'))
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
