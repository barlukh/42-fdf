# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/11 17:07:44 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra 
LFLAGS = -ldl -lglfw -lm -lmlx42 -pthread
RM = rm -f

HDRS = ft_fdf.h
OBJS = $(SRCS:.c=.o)
SRCS =	ft_camera.c \
		ft_draw.c \
		ft_get_next_line.c \
		ft_main.c \
		ft_parse.c \
		ft_split.c \
		ft_utils_exit.c \
		ft_utils_list.c \
		ft_utils_other.c \
		ft_utils_string.c \

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
