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

#----------------------------------------------------------------Libraries path
LIB42   := ./Lib42

#-----------------------------------------------------------------------Headers
HEADERS	:= -I ./include -I $(LIB42)/includ
INC_READLINE = -I/Users/$(USER)/.brew/opt/readline/include

#---------------------------------------------------------------------Libraries
LIBS	:= $(LIB42)/libft.a
LIB_READLINE = -L/Users/$(USER)/.brew/opt/readline/lib

#------------------------------------------------------------------------Source
SRC     := src/main.c
	   src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c \
	   src/builtins/builtin_exit.c src/builtins/builtin_export.c src/builtins/builtin_pwd.c \
	   src/builtins/builtin_unset.c src/builtins/builtins.c \
	   src/exec/child.c src/exec/dollarsign.c src/exec/errors.c src/exec/input_op.c \
	   src/exec/output_op.c src/exec/path.c src/exec/start.c src/exec/utils.c \
	   src/parsing/parse/check_commands2.c src/parsing/state_machine/char_machine.c \
	   src/parsing/state_machine/error_machine.c src/parsing/state_machine/lexe.c \
	   src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_machine.c \
	   src/parsing/parser.c \
	   src/utils/arg_list_actions/add_arg_node.c \
	   src/utils/cmd_list_actions/add_cmd_node.c src/utils/cmd_list_actions/add_inout_node.c \
	   src/utils/cmd_list_actions/print_cmd.c \
	   src/utils/envp_parser/parse_list_envp.c src/utils/envp_parser/parse_array_envp.c \
	   src/utils/errors/1.c src/utils/errors/258.c \
	   src/utils/history/history.c \
	   src/utils/I_want_to_break_free/parser_free.c \
	   src/utils/token_list_actions/add_tolken.c src/utils/token_list_actions/print_tolkens.c \
	   src/utils/token_list_actions/search_token.c

#-----------------------------------------------------------------------Objects
OBJS	:= ${SRC:.c=.o}

#---------------------------------------------------------------------Directory
OBJ_DIR := objs/
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR), $(OBJS))

#-----------------------------------------------------------------OS Dependency
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Mac)
	HEADERS += $(INC_READLINE)
	LIBS += $(LIB_READLINE)
else
	CC=cc
endif

#-------------------------------------------------------------------------Rules
all: $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(HEADERS)

lib42_build:
	@$(MAKE) -C $(LIB42)

$(NAME): lib42_build $(OBJECTS_PREFIXED)
	@$(CC) $(OBJECTS_PREFIXED) $(LIBS) $(HEADERS) -o $@ -lreadline

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all, clean, fclean, re, lib42_build