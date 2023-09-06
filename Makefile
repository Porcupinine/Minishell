# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: domi <domi@student.42.fr>                    +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/07 11:56:57 by dmaessen      #+#    #+#                  #
#    Updated: 2023/09/06 00:13:59 by laura         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------Executable
NAME	:= minishell

#----------------------------------------------------------------------Compiler
CC 	:=  gcc

#-------------------------------------------------------------------------Flags
CFLAGS	+= -Wextra -Wall -Werror
ASANFLAGS += -fsanitize=address -g #-fsanitize=leak

#----------------------------------------------------------------Libraries path
LIB42   := ./Lib42

#-----------------------------------------------------------------------Headers
HEADERS	:= -I ./include -I $(LIB42)/include
RL_HEARDERS	:= -I/Users/$(USER)/.brew/opt/readline/include

#---------------------------------------------------------------------Libraries
LIBS	:= $(LIB42)/libft.a
RL_LIB	:= -L/Users/$(USER)/.brew/opt/readline/lib

#------------------------------------------------------------------------Source
SRC     := src/main.c \
	   src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c \
	   src/builtins/builtin_exit.c src/builtins/builtin_export.c src/builtins/builtin_export3.c \
	   src/builtins/builtin_pwd.c \
	   src/builtins/builtin_unset.c src/builtins/builtins.c src/builtins/builtin_export2.c \
	   src/exec/fork2.c src/exec/dollarsign.c src/exec/errors.c src/exec/input_op.c \
	   src/exec/output_op.c src/exec/path.c src/exec/start.c src/exec/utils.c \
	   src/exec/fork.c src/exec/pipes.c src/exec/utils2.c src/exec/dollarsign2.c \
	   src/parsing/parse/check_commands.c src/parsing/parse/heredoc.c \
	   src/parsing/parse/quotes.c \
	   src/parsing/state_machine/char_machine.c \
	   src/parsing/state_machine/error_machine.c src/parsing/state_machine/lexe.c \
	   src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_machine.c \
	   src/parsing/parser.c \
	   src/utils/cmd_list_actions/add_cmd_node.c src/utils/cmd_list_actions/add_inout_node.c \
	   src/utils/cmd_list_actions/print_cmd.c \
	   src/utils/envp_parser/parse_list_envp.c src/utils/envp_parser/parse_array_envp.c \
	   src/utils/errors/1.c src/utils/errors/127.c src/utils/errors/255.c \
	   src/utils/history/history.c \
	   src/utils/I_want_to_break_free/parser_free.c src/utils/I_want_to_break_free/parser_free_array.c \
	   src/utils/signal_handlers/signal_handlers.c src/utils/signal_handlers/signal_handlers2.c \
	   src/utils/token_list_actions/add_token.c src/utils/token_list_actions/print_tokens.c \
	   src/utils/token_list_actions/search_token.c 
	   

#-----------------------------------------------------------------------Objects
OBJS	:= $(SRC:.c=.o)

#---------------------------------------------------------------------Directory
OBJ_DIR := objs/
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR), $(OBJS))

#-------------------------------------------------------------------------Rules
all: $(NAME)

$(NAME): $(LIBS) $(OBJECTS_PREFIXED)
	$(CC) $(ASANFLAGS) $(CFLAGS) $(OBJECTS_PREFIXED) $(LIBS) $(HEADERS) -o $@ -lreadline
	@echo "MINIHELL is ready!"

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS)  -o $@ -c $<  $(HEADERS)

$(LIBS):
	@$(MAKE) -C $(LIB42)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIB42)


fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB42)

re: fclean all

.PHONY: all, clean, fclean, re, lib42_build