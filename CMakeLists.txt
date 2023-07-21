cmake_minimum_required(VERSION 3.25)
project(minishell C)
include_directories(${CMAKE_SOURCE_DIR}/Lib42/include)

#add_compile_options(-fsanitize=address -g3)
#add_link_options(-fsanitize=address)
#add_compile_options(-fsanitize=address -fsanitize=address)
#add_link_options(-fsanitize=address)
set(CMAKE_C_STANDARD 99)

add_executable(minishell src/main.c include/env_var.h include/minishell.h "src/parsing/env_variables /env_var.c" src/utils/arg_list_actions/add_arg_node.c src/parsing/state_machine/lexe.c src/utils/tolken_list_actions/add_tolken.c include/arg_list_actions.h include/tolken_list_actions.h src/utils/tolken_list_actions/print_tolkens.c include/lexical_analyzer.h src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_newline.c src/parsing/state_machine/space_newline.c src/parsing/state_machine/char_machine.c src/parsing/state_machine/error_machine.c src/parsing/parse/check_comands.c src/utils/tolken_list_actions/search_token.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
