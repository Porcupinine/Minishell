cmake_minimum_required(VERSION 3.25)
project(minishell C)
include_directories(${CMAKE_SOURCE_DIR}/Lib42/include)

#add_compile_options(-fsanitize=address -g3)
#add_link_options(-fsanitize=address)
#add_compile_options(-fsanitize=address -fsanitize=address)
#add_link_options(-fsanitize=address)
set(CMAKE_C_STANDARD 99)

add_executable(minishell src/main.c include/parser.h include/minishell.h "src/env_variables /env_var.c" src/arg_list_actions/add_arg_node.c src/parsing/lexe.c src/tolken_list_actions/add_tolken.c include/arg_list_actions.h include/tolken_list_actions.h src/tolken_list_actions/print_tolkens.c include/lexical_analyzer.h src/parsing/meta_machine.c src/parsing/space_newline.c src/parsing/space_newline.c src/parsing/char_machine.c src/parsing/error_machine.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
