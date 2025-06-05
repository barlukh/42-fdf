# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/05 11:08:28 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra 
LFLAGS = -ldl -lglfw -lm -lmlx42 -pthread
RM = rm -f

HEADERS = ft_fdf.h
OBJS = $(SRCS:.c=.o)
SRCS =	ft_config.c \
		ft_main.c \
		ft_printf_utils.c \
		ft_printf.c \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJS): $(HEADERS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
