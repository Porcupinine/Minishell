cmake_minimum_required(VERSION 3.25)
project(minishell C)
include_directories(${CMAKE_SOURCE_DIR}/Lib42/include)

<<<<<<< HEAD
add_compile_options(-fsanitize=address -g3)
add_link_options(-fsanitize=address)
=======
#add_compile_options(-fsanitize=address -fsanitize=address)
#add_link_options(-fsanitize=address)
>>>>>>> 6b6bf631dbea0ae153cf54321488ef9e3c32cd25
set(CMAKE_C_STANDARD 99)

add_executable(minishell src/main.c include/parser.h include/minishell.h src/parsing/parsing.c src/parsing/env_var.c src/arg_list_actions/add_arg_node.c src/lexical_analyser/lexe.c src/tolken_list_actions/add_tolken.c include/arg_list_actions.h include/tolken_list_actions.h src/tolken_list_actions/print_tolkens.c include/lexical_analyzer.h src/lexical_analyser/meta_machine.c src/lexical_analyser/space_newline.c src/lexical_analyser/quotes_machine.c Lib42/libft_src/ft_charjoin.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
