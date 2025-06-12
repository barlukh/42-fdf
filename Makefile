# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 08:42:48 by bgazur            #+#    #+#              #
#    Updated: 2025/06/12 15:16:25 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		fdf
BONUS =		fdf_bonus
CC = 		cc
CFLAGS =	-Wall -Werror -Wextra 
LFLAGS =	-ldl -lglfw -lm -lmlx42 -pthread
RM = 		rm -f

HDRS =		ft_fdf.h

OBJS =		$(SRCS:.c=.o)

OBJS_B =	${SRCS_B:.c=.o}

SRCS =		ft_camera.c \
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

SRCS_B =	ft_camera_bonus.c \
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

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(BONUS): $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(BONUS) $(LFLAGS)

$(OBJS): $(HDRS)

$(OBJS_B): $(HDRS)

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
