# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/12 20:51:30 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		fdf
BONUS =		fdf_bonus
CC = 		cc
CFLAGS =	-Wall -Werror -Wextra -O3
LFLAGS =	-ldl -lglfw -lm -lmlx42 -pthread
RM = 		rm -f

HDRS =		ft_fdf.h

OBJ_DIR = 	objects

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

OBJS_B = $(SRCS_B:%.c=$(OBJ_DIR)/%.o)

SRCS = 		ft_camera.c \
			ft_config.c \
			ft_draw.c \
			ft_get_next_line.c \
			ft_main.c \
			ft_parse.c \
			ft_split.c \
			ft_utils_exit.c \
			ft_utils_list.c \
			ft_utils_other.c \
			ft_utils_string.c

SRCS_B = 	ft_camera_bonus.c \
			ft_config.c \
			ft_draw.c \
			ft_get_next_line.c \
			ft_main.c \
			ft_parse.c \
			ft_split.c \
			ft_utils_exit.c \
			ft_utils_list.c \
			ft_utils_other.c \
			ft_utils_string.c

all: $(OBJ_DIR) $(OBJS) $(NAME)

bonus: $(OBJ_DIR) $(OBJS_B) $(BONUS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(BONUS): $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(BONUS) $(LFLAGS)

clean:
	$(RM) $(OBJS)

clean_bonus:
	$(RM) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

fclean_bonus: clean_bonus
	$(RM) $(BONUS)

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re re_bonus
