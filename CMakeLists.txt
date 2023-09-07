cmake_minimum_required(VERSION 3.25)
project(minishell C)
include_directories(${CMAKE_SOURCE_DIR}/Lib42/include SYSTEM/Users/lpraca-l/.brew/opt/readline/include)

#add_compile_options(-fsanitize=address -g3)
#add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=address -fsanitize=leak -g3)
add_link_options(-fsanitize=address -fsanitize=leak)
#add_compile_options(-Wall -Werror -Wextra)

set(CMAKE_C_STANDARD 99)

add_custom_target(
        extern_lib
		BYPRODUCTS ${CMAKE_SOURCE_DIR}/Lib42/libft.a
		COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Lib42/
)

add_executable(minishell src/main.c
		src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c
		src/builtins/builtin_exit.c src/builtins/builtin_export.c src/builtins/builtin_pwd.c
		src/builtins/builtin_unset.c src/builtins/builtins.c src/builtins/builtin_export2.c
		src/builtins/builtin_export3.c
		src/exec/dollarsign.c src/exec/dollarsign2.c src/exec/errors.c src/exec/input_op.c
		src/exec/output_op.c src/exec/path.c src/exec/start.c src/exec/utils.c
		src/exec/fork.c src/exec/fork2.c src/exec/pipes.c
		src/exec/utils2.c
		src/parsing/parse/check_commands.c src/parsing/state_machine/char_machine.c
		src/parsing/parse/heredoc.c
		src/parsing/state_machine/error_machine.c src/parsing/state_machine/lexe.c
		src/parsing/state_machine/meta_machine.c src/parsing/state_machine/space_machine.c
		src/parsing/parser.c
		src/utils/cmd_list_actions/add_cmd_node.c src/utils/cmd_list_actions/add_inout_node.c
		src/utils/cmd_list_actions/print_cmd.c
		src/utils/envp_parser/parse_list_envp.c src/utils/envp_parser/parse_array_envp.c
		src/utils/errors/1.c src/utils/errors/1_b.c src/utils/errors/127.c src/utils/errors/255.c
		src/utils/history/history.c
		src/utils/I_want_to_break_free/parser_free.c src/utils/I_want_to_break_free/parser_free_array.c
		src/utils/signal_handlers/signal_handlers.c src/utils/signal_handlers/signal_handlers2.c
		src/utils/token_list_actions/add_token.c src/utils/token_list_actions/print_tokens.c
		src/utils/token_list_actions/search_token.c
		src/parsing/parse/quotes.c)

target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/Lib42/libft.a -lreadline)
target_link_directories(minishell PRIVATE /Users/lpraca-l/.brew/opt/readline/lib)
add_dependencies(minishell extern_lib)
