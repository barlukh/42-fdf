/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:23:13 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/17 09:00:51 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_BONUS_H
# define FT_FDF_BONUS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <math.h>
# include <MLX42.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define WIDTH 2000
# define HEIGHT 2000

# define TRUE 1
# define FALSE 0

# define LIMIT_IN 20000
# define LIMIT_OUT 1

# define CONTRACTION 0.8
# define ENLARGEMENT 1.2
# define ROTATION_LEFT -0.05
# define ROTATION_RIGHT 0.05
# define TRANSLATION 30

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/** Struct for x, y, and z coordinates and color information.
 * @param x x-axis.
 * @param y y-axis.
 * @param z z-axis.
 * @param color Color in RGB hexadecimal format.
 */
typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}	t_point;

/** Configuration and helper variables.
 * @param c Helper variable for argument validation.
 * @param center_x Center point of the window on the x-axis.
 * @param center_y Center point of the window on the y-axis.
 * @param x_min Minimum x value for a bounding box.
 * @param x_max Maximum x value for a bounding box.
 * @param x_temp Temporary variable for storing x value.
 * @param y_min Minimum y value for a bounding box.
 * @param y_max Maximum y value for a bounding box.
 * @param y_temp Temporary variable for storing y value.
 * @param c_flag Flag to indicate if object is fully colored.
 * @param fd File descriptor.
 * @param i Iterator variable.
 * @param j Iterator variable.
 * @param k Iterator variable.
 * @param line_size Number of points on one line (columns).
 * @param lst_size Number of lines extracted (rows).
 * @param x0 Variable for the Bresenham’s line algorithm.
 * @param y0 Variable for the Bresenham’s line algorithm.
 * @param img Allocated MLX image handle.
 * @param mlx The MLX instance handle.
 * @param p Original x, y, and z coordinates and color information.
 * @param pr Copied 'p' struct used for calculating different projections.
 */
typedef struct s_config
{
	char		*c;
	double		center_x;
	double		center_y;
	double		x_min;
	double		x_max;
	double		x_temp;
	double		y_min;
	double		y_max;
	double		y_temp;
	int			c_flag;
	int			fd;
	int			i;
	int			j;
	int			k;
	int			line_size;
	int			lst_size;
	int			x0;
	int			y0;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_point		*p;
	t_point		*pr;
}	t_config;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Finds the min and max coordinate for x and y.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_bounding_min_max(t_config *cfg);

/** Sets the point matrix to a specified projection.
 * @param cfg Configuration and helper variables.
 * @param f Function for setting a chosen projection.
 * @return 0 on SUCCESS, 1 on FAILURE.
 */
int		ft_config_matrix(t_config *cfg, void (*f)(t_config *));

/** Counts a centroid of an object.
 * @param cfg Configuration and helper variables.
 * @param c_x Center point of an object on the x-axis (centroid).
 * @param c_y Center point of an object on the y-axis (centroid).
 * @return None.
 */
void	ft_count_centroid(t_config *cfg, double *c_x, double *c_y);

/** Sets every pixel on the screen to a specified color.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_fill_screen(t_config *cfg);

/** Callback function that executes when a key event occurs.
 * @param k Data struct related to the mlx_key_hook function.
 * @param param An additional optional parameter.
 * @return None.
 */
void	ft_key_hook(mlx_key_data_t k, void *param);

/** Converts coordinates into isometric projection.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_projection_isometric(t_config *cfg);

/** Converts coordinates into trimetric projection.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_projection_trimetric(t_config *cfg);

#endif
