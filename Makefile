# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:56:57 by dmaessen          #+#    #+#              #
#    Updated: 2023/08/09 13:12:35 by dmaessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------Executable
NAME	:= minishell

#----------------------------------------------------------------------Compiler
CC 	:=  -gcc

#-------------------------------------------------------------------------Flags
CFLAGS	+= -Wextra -Wall -Werror
ASANFLAGS += -fsanitize=address -fsanitize=leak
LIB_READLINE = -L/Users/dmaessen/.brew/opt/readline/lib #-L/Users/lpraca-l/.brew/opt/readline/lib
INC_READLINE = -I/Users/dmaessen/.brew/opt/readline/include #-I/Users/lpraca-l/.brew/opt/readline/include

#----------------------------------------------------------------Libraries path
LIB42   := ./Lib42

#-----------------------------------------------------------------------Headers
HEADERS	:= -I ./include -I $(LIB42)/include

#---------------------------------------------------------------------Libraries
LIBS	:= $(LIB42)/libft.a

#------------------------------------------------------------------------Source
SRC     := src/main.c src/utils/arg_list_actions/add_arg_node.c src/parsing/state_machine/lexe.c \
        src/utils/tolken_list_actions/add_tolken.c \
        src/utils/tolken_list_actions/print_tolkens.c \
        src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_newline.c \
        src/parsing/state_machine/space_newline.c src/parsing/state_machine/char_machine.c \
        src/parsing/state_machine/error_machine.c src/parsing/parse/check_comands.c \
        src/utils/tolken_list_actions/search_token.c \
        src/utils/cmd_list_actions/add_inout_node.c src/utils/cmd_list_actions/print_cmd.c \
        src/utils/cmd_list_actions/add_cmd_node.c src/utils/history/history.c \
        src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c \
        src/builtins/builtin_exit.c src/builtins/builtin_export.c src/builtins/builtin_pwd.c \
        src/builtins/builtin_unset.c src/builtins/builtins.c src/exec/child.c src/exec/dollarsign.c \
        src/exec/errors.c src/exec/input_op.c src/exec/output_op.c src/exec/path.c src/exec/start.c \
        src/exec/utils.c

#-----------------------------------------------------------------------Objects
OBJS	:= ${SRC:.c=.o}

#---------------------------------------------------------------------Directory
OBJ_DIR := objs/
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR), $(OBJS))

#-------------------------------------------------------------------------Rules
all: $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(HEADERS) ${INC_READLINE}

lib42_build:
	@$(MAKE) -C $(LIB42)

$(NAME): lib42_build $(OBJECTS_PREFIXED)
	@$(CC) $(OBJECTS_PREFIXED) $(LIBS) $(HEADERS) -o $@ -lreadline ${LIB_READLINE}

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all, clean, fclean, re, lib42_build