# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:56:57 by dmaessen          #+#    #+#              #
#    Updated: 2023/06/13 15:12:08 by dmaessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex_bonus.c stdin_bonus.c heredoc_bonus.c paths_bonus.c errors_free_bonus.c cmd_bonus.c child_bonus.c \

LIBFT = Lib42/libft.a

CC = cc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_FILES   = $(SRC)

all: $(NAME)

$(NAME): $(SRC_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft/

clean:
	make clean -C libft/
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re