cmake_minimum_required(VERSION 3.25)
project(minishell C)
include_directories(${CMAKE_SOURCE_DIR}/Lib42/include SYSTEM/Users/lpraca-l/.brew/opt/readline/include)

add_compile_options(-fsanitize=address -g3)
add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=address -fsanitize=address)
add_link_options(-fsanitize=address)
#add_compile_options(-Wall -Werror -Wextra)

set(CMAKE_C_STANDARD 99)

add_executable(minishell src/main.c include/env_var.h include/minishell.h
        src/utils/arg_list_actions/add_arg_node.c src/parsing/state_machine/lexe.c
        src/utils/tolken_list_actions/add_tolken.c include/token_list_actions.h
        src/utils/tolken_list_actions/print_tolkens.c include/lexical_analyzer.h
        src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_newline.c
        src/parsing/state_machine/space_newline.c src/parsing/state_machine/char_machine.c
        src/parsing/state_machine/error_machine.c src/parsing/parse/check_comands.c
        src/utils/tolken_list_actions/search_token.c include/cmd_list_actions.h
        src/utils/cmd_list_actions/add_inout_node.c src/utils/cmd_list_actions/print_cmd.c
        src/utils/cmd_list_actions/add_cmd_node.c src/utils/history/history.c src/utils/I_want_to_break_free/parser_free.c include/I_want_to_break_free.h src/parsing/parser.c src/utils/envp_parser/parse_array_envp.c include/envp_parser.h src/utils/envp_parser/parse_list_envp.c src/parsing/parse/check_commands2.c src/utils/errors/1.c src/utils/errors/258.c include/errors.h)
#        include/builtins.h src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c
#        src/builtins/builtin_exit.c src/builtins/builtin_export.c src/builtins/builtin_pwd.c
#        src/builtins/builtin_unset.c src/builtins/builtins.c src/exec/child.c src/exec/dollarsign.c
#        src/exec/errors.c src/exec/input_op.c src/exec/output_op.c src/exec/path.c src/exec/start.c
#        src/exec/utils.c)

target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
target_link_directories(minishell PRIVATE /Users/lpraca-l/.brew/opt/readline/lib)
