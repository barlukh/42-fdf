/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:23:13 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/06 15:33:56 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <limits.h>
# include <MLX42.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define BASE10 10
# define BASE16 16
# define DECIMAL "0123456789"
# define HEX_LCASE "0123456789abcdef"
# define HEX_UCASE "0123456789ABCDEF"

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
typedef struct s_struct
{
	char	*cache;
	char	*br;
	ssize_t	read_bytes;
	char	*new_line;
}	t_struct;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Configurates the parameters of the window.
 * @param mlx The MLX instance handle.
 * @param cfg Struct containing basic variables for setting up the program.
 * @return None.
 */
void	ft_config_window(mlx_t *mlx, t_config *cfg);

/**	Prints an error message with the corresponding error number (errno).
 * @param mlx The MLX instance handle.
 * @return Errno.
 */
int		ft_exit(mlx_t *mlx);

/** Reads and returns a line from a file pointed to by a file descriptor.
 * @param fd File descriptor to read data from.
 * @return Read line (string).
 */
char	*ft_get_next_line(int fd);

/** Callback function that executes when a key event occurs.
 * @param keydata Data related to the mlx_key_hook function.
 * @param param An additional optional parameter.
 * @return None.
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param);

/** Copies bytes from one memory area to another; the areas must not overlap.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/** Parses command line arguments checking for invalid input.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on SUCCESS, 1 on FAILURE.
 */
int		ft_parse_input(int argc, char **argv);

/** Writes a string with format specifiers into the standard output.
 * @param s String to write.
 * @param ... Additional variadic arguments matching format specifiers.
 * @return Number of characters written, -1 on error.
 */
int		ft_printf(const char *s, ...);

/** Writes a charater into the standard output.
 * @param c Character to write.
 * @return Number of characters written, -1 on error.
 */
int		ft_putchar(int c);

/** Writes a memory address of a pointer into the standard output.
 * @param p Memory address to write (represented as an integer).
 * @return Number of characters written, -1 on error.
 */
int		ft_putnbr_p(uintptr_t p);

/** Writes a signed integer into the standard output.
 * @param n Integer to write.
 * @return Number of characters written, -1 on error.
 */
int		ft_putnbr_s(int n);

/** Writes an unsigned integer into the standard output.
 * @param n Integer to write.
 * @param base Base of the integer.
 * @param style Style format indicator for hexadecimal letters.
 * @return Number of characters written, -1 on error.
 */
int		ft_putnbr_u(unsigned int n, unsigned int base, const char *style);

/** Writes a string into the standard output.
 * @param s String to write.
 * @return Number of characters written, -1 on error.
 */
int		ft_putstr(const char *s);

/** Scans a string for the first instance of 'c'.
 * @param s String to search.
 * @param c Character to search for, passed as an int.
 * @return Pointer to the matching location, 'NULL' if no match.
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
 * @return New substring, 'NULL' if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
