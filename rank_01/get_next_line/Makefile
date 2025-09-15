# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 17:52:46 by maprunty          #+#    #+#              #
#    Updated: 2025/09/15 07:41:39 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftgnl.a

INC 	:= -Iinclude
FD 		:= -D FD=3
CC      := gcc -g ${FD}
CFLAGS  := -Wall -Wextra -Werror $(INC)

AR		:= ar
ARFLAGS := -rcs

S_FILES	:= get_next_line.c get_next_line_utils.c
SRC		:= $(S_FILES:%.c=src/%.c)
OBJ     := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ) 
	$(AR) $(ARFLAGS) $@ $^

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
