# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/17 14:21:46 by maprunty          #+#    #+#              #
#    Updated: 2025/12/17 22:20:44 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	:= push_swap_tst

LIBS	:= ../lib/libft.a #lib/libft.a
PS		:= ../
PSBIN	:= push_swap

INC 	:= -Iinclude
CC      := gcc -g 
CFLAGS  := $(INC) #-Wall -Wextra -Werror 

S_FILES	:= ps_test.c ft_itoa.c ft_split.c #pufsh_swap.c p #ft_help.c 

SRC	:= $(S_FILES)

OBJ     := $(SRC:%.c=%.o)

all: $(PSBIN) $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PSBIN):
	$(MAKE) -C $(PS)
	mv $(PS)/$@ $(NAME) . 

debug: dbgclean all 
	$(CC) -no-pie main.c $(NAME) 

%.o: %.c 
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
