# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:56:57 by dmaessen          #+#    #+#              #
#    Updated: 2023/07/18 16:47:11 by dmaessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------Executable
NAME	:= minishell

#----------------------------------------------------------------------Compiler
CC 		=  -gcc

#-------------------------------------------------------------------------Flags
CFLAGS	+= -Wextra -Wall -Werror
ASANFLAGS += -fsanitize=address -fsanitize=leak

#----------------------------------------------------------------Libraries path
LIB42   := ./lib42

#-----------------------------------------------------------------------Headers
HEADERS	:= -I ./include -I $(LIB42)/include

#---------------------------------------------------------------------Libraries
LIBS	:= $(LIB42)/libft.a

#------------------------------------------------------------------------Source
SRC     := src/arg_list_actions/add_new_node.c \
		src/exec_pipes/pipex.c src/exec_pipes/stdin.c src/exec_pipes/heredoc.c \
		src/exec_pipes/path.c src/exec_pipes/errors_free.c src/exec_pipes/cmd.c src/exec_pipes/child.c \
		src/parsing/env_var.c src/parsing/lexycal_analizer.c src/parsing/parsing.c \
		main.c \

#-----------------------------------------------------------------------Objects
OBJS	:= ${SRC:.c=.o}

#---------------------------------------------------------------------Directory
OBJ_DIR := objs/
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR), $(OBJS))

#-------------------------------------------------------------------------Rules
all: $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

lib42_build:
	@$(MAKE) -C $(LIB42)

$(NAME): lib42_build $(OBJECTS_PREFIXED)
	@$(CC) $(OBJECTS_PREFIXED) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all, clean, fclean, re, lib42_build