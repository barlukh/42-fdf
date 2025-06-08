/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:23:13 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/08 14:36:39 by bgazur           ###   ########.fr       */
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

/** Holds system configuration informaton.
 * @param monitor_width Width of the monitor.
 * @param monitor_height Height of the monitor.
 */
typedef struct s_config
{
	int32_t	monitor_width;
	int32_t	monitor_height;
}	t_config;

/** Holds variables related to the ft_get_next_line function.
 * @param cache Helper string allowing continuous read from the buffer.
 * @param br Character signaling break of the line (either '\n' or '\0').
 * @param read_bytes Return value from the read() function.
 * @param new_line Allocated line to return.
 */
typedef struct s_gnl
{
	char	*cache;
	char	*br;
	ssize_t	read_bytes;
	char	*new_line;
}	t_gnl;

/** Linked list struct storing the content of the map (one line per node).
 * @param content Line from the map file stored as a string.
 * @param next Address of the next node.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/** Struct for x, y and z coordinates.
 * @param x X-axis.
 * @param y Y-axis.
 * @param z Z-axis.
 */
typedef struct s_coordinates
{
	int	x;
	int	y;
	int	z;
}	t_coordinates;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**	Prints an error message according to the error number (mlx_errno).
 * @return Errno.
 */
int		ft_exit_msg(void);

/**	Prints an error message according to the error number (mlx_errno).
 * @param mlx The MLX instance handle.
 * @return Errno.
 */
int		ft_exit_term(mlx_t *mlx);

/** Reads and returns a line from a file pointed to by a file descriptor.
 * @param fd File descriptor to read data from.
 * @return Dynamically allocated line (string), NULL on error or EOF.
 */
char	*ft_get_next_line(int fd);

/** Parses command line arguments.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on SUCCESS, 1 on FAILURE.
 */
int		ft_init_parse(int argc, char **argv);

/** Configurates the parameters of the window.
 * @param mlx The MLX instance handle.
 * @param cfg Struct containing basic variables for setting up the program.
 * @return None.
 */
void	ft_init_window(mlx_t *mlx, t_config *cfg);

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

#endif
