# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yli <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 12:55:00 by yli               #+#    #+#              #
#    Updated: 2023/04/10 12:55:06 by yli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Werror -Wextra
HEADER = philo.h
CC = cc
SRCS = main.c 0ft_utils.c 1check_input.c 2ft_init.c 3ft_execute.c 4ft_free.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -g3 -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean
	make all

.PHONY: all clean fclean re


