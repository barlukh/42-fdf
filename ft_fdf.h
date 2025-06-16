/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:23:13 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/16 08:59:02 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <fcntl.h>
# include <math.h>
# include <MLX42.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h> // REMOVE BEFORE SUBMISSION!

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# define WIDTH 2000
# define HEIGHT 2000

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

/** Variables used by Bresenham's line algorithm.
 * @param dx Absolute difference between points (horizontal distance).
 * @param dy Absolute difference between points, negated (vertical distance).
 * @param err Error value tracking when to move in each direction.
 * @param e2 Temporary variable used to decide whether to adjust x or y.
 * @param sx Step direction for x.
 * @param sy Step direction for y.
 */
typedef struct s_draw
{
	int	dx;
	int	dy;
	int	err;
	int	e2;
	int	sx;
	int	sy;
}	t_draw;

/** Linked list struct storing the content of the map (one line per node).
 * @param content Line from the map file stored as a string.
 * @param next Address of the next node.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Converts a string to an integer (detects hex values).
 * @param s String to be converted.
 * @return Converted string as an int.
 */
int		ft_atoi_base(const char *s);

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

/** Configurates the initial window.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_config_window(t_config *cfg);

/** Main hook for drawing the map.
 * @param param An additional optional parameter.
 * @return None.
 */
void	ft_draw(void *param);

/** Sets an error message according to the mlx_errno and frees memory.
 * @param line Allocated string (line).
 * @param lst Allocated linked list for extracting the map file.
 * @param cfg Configuration and helper variables.
 * @param flag Error flag to set the correct mlx_errno message.
 * @return EXIT FAILURE.
 */
int		ft_error_extract(char *line, t_list **lst, t_config *cfg, int flag);

/**	Prints an error message according to the mlx_errno and frees memory.
 * @param cfg Configuration and helper variables.
 * @return Errno.
 */
int		ft_error_img(t_config *cfg);

/**	Prints an error message according to mlx_errno.
 * @return Errno.
 */
int		ft_error_msg(void);

/**	Prints an error message according to the mlx_errno and frees memory.
 * @param cfg Configuration and helper variables.
 * @return Errno.
 */
int		ft_error_pr(t_config *cfg);

/** Sets an error message according to the mlx_errno and frees memory.
 * @param lst Allocated linked list for extracting the map file.
 * @param cfg Configuration and helper variables.
 * @return EXIT FAILURE.
 */
int		ft_error_sort(t_list **lst, t_config *cfg);

/**	Prints an exit message and frees memory.
 * @param cfg Configuration and helper variables.
 * @return Errno.
 */
int		ft_exit_terminate(t_config *cfg);

/** Sets every pixel on the screen to a specified color.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_fill_screen(t_config *cfg);

/** Frees memory allocated by ft_split() for splitting each line.
 * @param line Allocated string (line).
 * @return None.
 */
void	ft_free_split(char **line);

/** Reads and returns a line from a file pointed to by a file descriptor.
 * @param fd File descriptor to read data from.
 * @return Dynamically allocated line (string), NULL on error or EOF.
 */
char	*ft_get_next_line(int fd);

/** Callback function that executes when a key event occurs.
 * @param k Data struct related to the mlx_key_hook function.
 * @param param An additional optional parameter.
 * @return None.
 */
void	ft_key_hook(mlx_key_data_t k, void *param);

/** Adds a node at the end of a linked list.
 * @param lst Address of a pointer to the first node of the list.
 * @param new Address of the node to add.
 * @return None.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/** Deletes and frees a given node and all its successors.
 * @param lst Address of a pointer to the node.
 * @return None.
 */
void	ft_lstclear(t_list **lst);

/** Creates a new node in a linked list.
 * @param content Content to store in the new node.
 * @return Pointer to the new node.
 */
t_list	*ft_lstnew(void *content);

/** Counts the number of nodes in a linked list.
 * @param lst First node of the list.
 * @return Length of the list.
 */
int		ft_lstsize(t_list *lst);

/** Copies bytes from one memory area to another; the areas must not overlap.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/** Parses command line arguments.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param cfg Configuration and helper variables.
 * @return 0 on SUCCESS, 1 on FAILURE.
 */
int		ft_parse(int argc, char **argv, t_config *cfg);

/** Converts coordinates into isometric projection.
 * @param cfg Configuration and helper variables.
 * @return None.
 */
void	ft_projection_isometric(t_config *cfg);

/** Writes a string into the standard output followed by a newline character.
 * @param s String to write.
 * @return None.
 */
void	ft_putstr(const char *s);

/** Splits a string according to a specified delimiter.
 * @param s String to split.
 * @param c Delimiter.
 * @return Array of new strings, NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c);

/** Scans a string for the first instance of 'c'.
 * @param s String to search.
 * @param c Character to search for, passed as an int.
 * @return Pointer to the matching location, NULL if no match.
 */
char	*ft_strchr(const char *s, int c);

/** Calculates the length of a string.
 * @param s String to calculate the length of.
 * @return Number of bytes in the passed string.
 */
size_t	ft_strlen(const char *s);

/** Creates a substring using dynamic memory allocation.
 * @param s Source string for the substring.
 * @param start Starting index.
 * @param len Length of the substring.
 * @return New substring, NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/** Counts how many words are in a string based on a delimiter 'c'.
 * @param s String to check.
 * @param c Delimiter.
 * @return Word count.
 */
int		ft_word_count(char const *s, char c);

#endif
