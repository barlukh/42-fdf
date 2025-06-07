# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/07 11:34:20 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra 
LFLAGS = -ldl -lglfw -lm -lmlx42 -pthread
RM = rm -f

HDRS = ft_fdf.h
OBJS = $(SRCS:.c=.o)
SRCS =	ft_get_next_line.c \
		ft_init_list.c \
		ft_init_utils.c \
		ft_init.c \
		ft_main.c \
		ft_printf_utils.c \
		ft_printf.c \
		ft_split_utils.c \
		ft_split.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJS): $(HDRS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
