# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 00:35:07 by maprunty          #+#    #+#              #
#    Updated: 2025/12/16 01:09:23 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= push_swap

LIBS	:= lib/libft.a #lib/libft.a

INC 	:= -Iinclude
CC      := gcc -g 
CFLAGS  := $(INC) #-Wall -Wextra -Werror 

S_FILES	:= main.c misc.c ft_help.c rotate.c push.c swap.c #push_swap.c 

SRC	:= $(S_FILES:%.c=src/%.c)

OBJ     := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

debug: dbgclean bonus
	$(CC) -no-pie main.c $(NAME) 

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

dbgclean: fclean
	rm -rf a.out

re: fclean all

.PHONY: all clean fclean re
