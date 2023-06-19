cmake_minimum_required(VERSION 3.25)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell src/main.c include/parser.h include/minishell.h src/parsing/parsing.c src/parsing/lexycal_analizer.c)
target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
