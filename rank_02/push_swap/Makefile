# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 00:35:07 by maprunty          #+#    #+#              #
#    Updated: 2026/01/01 23:47:27 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= push_swap

LIB     := lib
LFT     := libft.a

INC 	:= -Iinclude
CC      := gcc -g # -fsanitize=address 
CFLAGS  := $(INC) -Wall -Wextra -Werror 

S_FILES	:=	algos.c  clean.c  elements.c  helpers.c  lists.c stacks.c  swap.c\
			maths.c  parse.c  print.c  push.c  push_swap.c  rot.c  rrot.c
SRC		:= $(S_FILES:%.c=src/%.c)
OBJ     := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(LFT) $(OBJ) 
	$(CC) $(CFLAGS) $^ $(LFT) -o $@

$(LFT):
	$(MAKE) -C $(LIB)
	mv  $(LIB)/$@ . 

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

clean:
	$(MAKE) -C $(LIB) clean
	rm -rf $(OBJ) $(LFT)

fclean: clean
	$(MAKE) -C $(LIB) fclean
	rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re
