# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 17:52:46 by maprunty          #+#    #+#              #
#    Updated: 2025/11/11 08:23:57 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a

LIB		:= libft
LFT		:= libft.a
INC 	:= include
CC      := gcc -g
CFLAGS  := -Wall -Wextra -Werror -I$(INC) 

AR		:= ar
ARFLAGS := -rcs

S_FILES	:= ft_printf.c ft_parse.c ft_render.c ft_utils.c ft_atoi_base.c ft_putnbr_base.c
SRC		:= $(S_FILES:%.c=src/%.c)
OBJ     := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

bonus: all

debug: dbgclean bonus
	gcc -g main.c $(NAME) 

$(LFT):
	$(MAKE) -C $(LIB)
	mv  $(LIB)/$@ $(NAME) 

$(NAME): $(LFT) $(OBJ) 
	$(AR) $(ARFLAGS)  $@  $(OBJ)

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@ 

obj:
	mkdir -p $@

clean:
	$(MAKE) -C $(LIB) clean
	rm -rf $(OBJ) 

fclean: clean
	$(MAKE) -C $(LIB) fclean
	rm -rf $(NAME)

dbgclean: fclean
	rm -rf a.out

re: fclean all

.PHONY: all clean fclean re
