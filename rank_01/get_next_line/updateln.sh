#!/bin/bash

rm ./libft/libft.a
rm ./libft/libftftprintf.a
rm ./include/libft.h
rm ./include/ft_printf.h


ln /data/code/42_cursus/rank_00/libft/libft.a libft/
ln /data/code/42_cursus/rank_00/libft/include/libft.h include/

ln /data/code/42_cursus/rank_01/ft_printf/libftftprintf.a libft/ 
ln /data/code/42_cursus/rank_01/ft_printf/include/ft_printf.h include/ 
