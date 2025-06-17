# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/17 09:50:34 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		fdf
BONUS =		fdf_bonus
CC = 		cc
CFLAGS =	-Wall -Werror -Wextra -O2
LFLAGS =	-ldl -lglfw -lm -lmlx42 -pthread
RM = 		rm -f

HDR =		ft_fdf.h
HDR_B =		ft_fdf_bonus.h

OBJ_DIR = 	objects
OBJ_DIR_B =	objects_b

OBJS =		$(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_B =	$(SRCS_B:%.c=$(OBJ_DIR_B)/%.o)

SRCS = 		ft_config.c \
			ft_draw.c \
			ft_get_next_line.c \
			ft_main.c \
			ft_parse.c \
			ft_projections.c \
			ft_split.c \
			ft_transformations.c \
			ft_utils_errors.c \
			ft_utils_list.c \
			ft_utils_other.c \
			ft_utils_string.c \

SRCS_B = 	ft_config.c \
			ft_draw.c \
			ft_get_next_line.c \
			ft_main.c \
			ft_parse.c \
			ft_projections_bonus.c \
			ft_split.c \
			ft_transformations_bonus.c \
			ft_utils_errors.c \
			ft_utils_list.c \
			ft_utils_other.c \
			ft_utils_string.c \

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(BONUS): $(OBJ_DIR_B) $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(BONUS) $(LFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_B):
	mkdir -p $(OBJ_DIR_B)

$(OBJ_DIR)/%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_B)/%.o: %.c $(HDR) $(HDR_B)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(OBJ_DIR_B) $(NAME) $(BONUS)

bonus: $(OBJ_DIR_B) $(BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
