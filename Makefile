##
## Makefile for  in /home/zellou_i/rendu/PSU_2013_nmobjdump
##
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
##
## Started on  Fri Mar 14 13:02:24 2014 ilyas zelloufi
## Last update Sun Mar 16 14:25:10 2014 ilyas zelloufi
##

CC = gcc

RM = rm -f

CFLAGS += -Wextra -Wall -Werror

LDFLAGS =

NAME_NM = ./nm/my_nm

NAME_OBJ = ./objdump/my_objdump

SRCS_NM = ./nm/my_nm.c \
	./nm/get_type.c \
	./nm/main.c

SRCS_OBJ = ./objdump/my_objdump.c

OBJS_NM = $(SRCS_NM:.c=.o)

OBJS_OBJ = $(SRCS_OBJ:.c=.o)

all: $(NAME_NM) $(NAME_OBJ)

nm: $(NAME_NM)

objdump: $(NAME_OBJ)

$(NAME_NM): $(OBJS_NM)
	 $(CC) $(OBJS_NM) -o $(NAME_NM) $(LDFLAGS)

$(NAME_OBJ): $(OBJS_OBJ)
	 $(CC) $(OBJS_OBJ) -o $(NAME_OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_OBJ)

fclean: clean
	$(RM) $(NAME_NM)
	$(RM) $(NAME_OBJ)

re: fclean all

.PHONY: all clean fclean re
