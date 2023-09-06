#--------------------------------------------------------------------Executable
NAME	:= libft.a

#----------------------------------------------------------------------Compiler
CC 		=  -gcc

#-------------------------------------------------------------------------Flags
CFLAGS	+= -Wextra -Wall -Werror -Wunreachable-code -Wno-unused-result -o0 -g
ASANFLAGS += -fsanitize=address -fsanitize=leak

#-----------------------------------------------------------------------Headers
HEADERS	:= -I ./include

#------------------------------------------------------------------------Source
SRC     := libft/ft_error.c libft/ft_atoi.c libft/ft_bzero.c \
libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c \
libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c \
libft/ft_itoa.c libft/ft_memcmp.c libft/ft_memcpy.c \
libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c \
libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c \
libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c \
libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c \
libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c \
libft/ft_tolower.c libft/ft_toupper.c libft/ft_strmapi.c \
libft/ft_striteri.c libft/ft_memchr.c libft/ft_lstnew.c \
libft/ft_lstadd_front.c libft/ft_lstsize.c libft/ft_lstlast.c \
libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c \
libft/ft_lstiter.c ft_printf/ft_printf.c \
ft_printf/ft_print_char_string.c ft_printf/ft_putnbr_base.c \
ft_printf/ft_pointer.c ft_printf/ft_putnbr_ulong.c \
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
libft/ft_charjoin.c get_next_line/get_next_line_exit.c \
get_next_line/get_next_line_b_exit.c get_next_line/get_next_line_b_utils.c

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

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)
	@echo "Lib42 is ready!"

clean:
	@rm -rf $(OBJ_DIR)
	@echo libft clean

fclean: clean
	@rm -f $(NAME)
	@echo libft fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx lib42_build