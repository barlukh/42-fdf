/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:23:13 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/10 11:48:37 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <fcntl.h>
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

# define WIDTH 1920
# define HEIGHT 1080

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/** Configuration and helper variables.
 * @param c Helper variable for argument validation.
 * @param split Temporary array to store the result of ft_split() into.
 * @param comparison_size Helper variable to compare the line_size to.
 * @param fd File descriptor.
 * @param line_size Number of points on one line (columns).
 * @param lst_size Number of lines extracted (rows).
 * @param i Iterator variable.
 * @param j Iterator variable.
 * @param k Iterator variable.
 * @param monitor_w Width of the monitor.
 * @param monitor_h Height of the monitor.
 */
typedef struct s_config
{
	char	*c;
	char	**split;
	int		comparison_size;
	int		fd;
	int		line_size;
	int		lst_size;
	size_t	i;
	size_t	j;
	size_t	k;
	int32_t	monitor_w;
	int32_t	monitor_h;
}	t_config;

/** Linked list struct storing the content of the map (one line per node).
 * @param content Line from the map file stored as a string.
 * @param next Address of the next node.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/** Struct for a point's x, y, and z coordinates and color information.
 * @param x X-axis.
 * @param y Y-axis.
 * @param z Z-axis.
 * @param color Color in RGB hexadecimal format.
 */
typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}	t_point;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Converts a string to an integer (detects hex values).
 * @param nptr String to be converted.
 * @return Converted string as an int.
 */
int		ft_atoi_base(const char *s);

/** Configurates the initial window.
 * @param mlx The MLX instance handle.
 * @param img Allocated MLX image handle.
 * @param cfg Struct containing basic variables for setting up the program.
 * @return None.
 */
void	ft_config_window(mlx_t *mlx,  mlx_image_t *img, t_config *cfg);

/** Sets an error message according to the mlx_errno and frees memory.
 * @param line Allocated string (line).
 * @param lst Allocated linked list for extracting the map file.
 * @param cfg Configuration variables of the array of points.
 * @param flag Error flag to set the correct mlx_errno message.
 * @return EXIT FAILURE.
 */
int		ft_error_extract(char *line, t_list **lst, t_config *cfg, int flag);

/**	Prints an error message according to the mlx_errno and frees memory.
 * @param mlx The MLX instance handle.
 * @param p Array of map points and their attributes.
 * @return Errno.
 */
int		ft_error_img(mlx_t *mlx, t_point *p);

/**	Prints an error message according to mlx_errno.
 * @return Errno.
 */
int		ft_error_msg(void);

/** Sets an error message according to the mlx_errno and frees memory.
 * @param lst Allocated linked list for extracting the map file.
 * @param p Array of map points and their attributes.
 * @return EXIT FAILURE.
 */
int		ft_error_sort(t_list **lst, t_point *p);

/**	Prints an error message according to the mlx_errno and frees memory.
 * @param mlx The MLX instance handle.
 * @param img Allocated MLX image handle.
 * @param p Array of map points and their attributes.
 * @return Errno.
 */
int		ft_exit_terminate(mlx_t *mlx, mlx_image_t *img, t_point *p);

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

/** Parses command line arguments.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param p Address of an array of map points and their attributes.
 * @param cfg Configuration variables of the array of points.
 * @return 0 on SUCCESS, 1 on FAILURE.
 */
int		ft_parse(int argc, char **argv, t_point **p, t_config *cfg);

/** Callback function that executes when a key event occurs.
 * @param keydata Data related to the mlx_key_hook function.
 * @param param An additional optional parameter.
 * @return None.
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param);

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
