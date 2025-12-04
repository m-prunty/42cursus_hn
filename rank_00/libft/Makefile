# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 17:52:46 by maprunty          #+#    #+#              #
#    Updated: 2025/12/04 22:34:26 by maprunty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libft

INC 	:= -Iinclude
CC      := gcc 
CFLAGS  := -Wall -Wextra -Werror $(INC)

AR		:= ar
ARFLAGS := -rcs

S_FILES		:=	ft_toupper.c ft_isalpha.c ft_isdigit.c ft_tolower.c ft_isalnum.c \
				ft_isascii.c ft_strchr.c ft_isprint.c ft_strrchr.c ft_strlen.c \
				ft_strncmp.c ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c \
				ft_memmove.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_calloc.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c 

B_FILES		:=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BT_FILES	:=	btree_apply_by_level.c\
				btree_apply_infix.c\
				btree_apply_prefix.c\
				btree_apply_suffix.c\
				btree_create_node.c\
				btree_insert_data.c\
				btree_level_count.c\
				btree_search_item.c\

P_FILES		:= ft_parse.c\
			   ft_printf.c\
			   ft_putnbr_base.c\
			   ft_render_chars.c\
			   ft_render_nums.c\
			   ft_utils.c\
			   handlers.c\
			   platform_dependent.c\


G_FILES	:= get_next_line_bonus.c\
			   get_next_line.c\
			   get_next_line_utils_bonus.c\
			   get_next_line_utils.c\


SRC		:= $(S_FILES:%.c=src/%.c)
BSRC	:= $(B_FILES:%.c=src/%.c)
BTSRC	:= $(BT_FILES:%.c=src/btree/%.c)
PSRC	:= $(P_FILES:%.c=src/printf/%.c)
GSRC	:= $(G_FILES:%.c=src/gnl/%.c)

OBJ     := $(patsubst src/%.c,obj/%.o,$(SRC))
BOBJ	:= $(patsubst src/%.c,obj/%.o,$(BSRC))
BTOBJ	:= $(patsubst src/btree/%.c,obj/%.o,$(BTSRC))
POBJ	:= $(patsubst src/printf/%.c,obj/%.o,$(PSRC))
GOBJ	:= $(patsubst src/gnl/%.c,obj/%.o,$(GSRC))

all: $(NAME)

$(NAME): $(OBJ) $(BOBJ) $(BTOBJ) $(POBJ) $(GOBJ)
	$(AR) $(ARFLAGS) $@.a $^

mand: $(OBJ) 
	$(AR) $(ARFLAGS) $(NAME)_mand.a $^

bonus: $(OBJ) $(BOBJ)
	$(AR) $(ARFLAGS) $(NAME)_ls.a $^

btree: $(OBJ) $(BOBJ) $(BTOBJ)
	$(AR) $(ARFLAGS) $(NAME)_bt.a $^

printf: $(OBJ) $(POBJ)
	$(AR) $(ARFLAGS) $(NAME)_print.a $^

gnl: $(OBJ) $(GOBJ)
	$(AR) $(ARFLAGS) $(NAME)_gnl.a $^

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/btree/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/printf/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/gnl/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME)%.a

re: fclean all

.PHONY: all clean fclean re
