/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:52:08 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/11 16:30:59 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	ft_atoi_base(const char *s)
{
	int	n;
	int	base;

	n = 0;
	base = 10;
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
	{
		base = 16;
		s += 2;
	}
	while (*s)
	{
		n *= base;
		if (*s >= '0' && *s <= '9')
			n += *s - '0';
		else if (base == 16 && *s >= 'A' && *s <= 'F')
			n += *s - 'A' + 10;
		else if (base == 16 && *s >= 'a' && *s <= 'f')
			n += *s - 'a' + 10;
		else
			break ;
		s++;
	}
	return (n);
}

void	ft_config_matrix(t_config *cfg)
{
	int	old_x;
	int	old_y;

	cfg->center_x = WIDTH / 2;
	cfg->center_y = HEIGHT / 2;
	cfg->i = 0;
	while (cfg->i < (cfg->line_size * cfg->lst_size))
	{
		old_x = cfg->p[cfg->i].x;
		old_y = cfg->p[cfg->i].y;
		cfg->p[cfg->i].x = (old_x + old_y) * cos(120);
		cfg->p[cfg->i].y = (old_y - old_x) * sin(120) - cfg->p[cfg->i].z;
		cfg->p[cfg->i].x = (cfg->center_x + (cfg->p[cfg->i].x * SPACE));
		cfg->p[cfg->i].y = cfg->center_y + cfg->center_y / 2
			+ (cfg->p[cfg->i].y * SPACE);
		cfg->i++;
	}
}

void	ft_config_window(t_config *cfg)
{
	mlx_get_monitor_size(0, &cfg->m_width, &cfg->m_height);
	mlx_set_window_pos(cfg->mlx, (cfg->m_width - WIDTH) / 2,
		(cfg->m_height - HEIGHT) / 2);
	mlx_set_window_limit(cfg->mlx, cfg->m_width / 4, cfg->m_height / 4,
		cfg->m_width - (cfg->m_width / 10),
		cfg->m_height - (cfg->m_height / 10));
	ft_fill_screen(cfg);
}

void	ft_free_split(char **line)
{
	size_t	i;

	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptrd;
	const unsigned char	*ptrs;
	size_t				i;

	ptrd = (unsigned char *)dest;
	ptrs = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptrd[i] = ptrs[i];
		i++;
	}
	return (dest);
}
