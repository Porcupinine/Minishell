//
// Created by Laura Praca Lacerda on 8/21/23.
//

#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H

#include "minishell.h"
#include "lexical_analyzer.h"

//-------------------------------------------------------------signal_handlers
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	set_signals(void);
void	return_prompt(void);
void	unset_signals(void );

//------------------------------------------------------------cmd_list_actions
/**
 * adds a command node to the command list
 * @param cmd pointer to the head of the list of commands
 * @param new_cmd new command node
 */
void	add_cmd_node(t_commands **cmd, t_commands *new_cmd);
/**
 * add infiles and outfiles to the list inside the new command node
 * @param cmd command node
 * @param str name of the file
 * @param type type of redirection
 */
void	add_inout(t_commands **cmd, char *str, enum s_type type);
/**
 * print the list of commands with list of infiles and outfiles if they exist
 * @param cmd pointer to the head of the command list
 */
void	print_cmd_list(t_commands *cmd);

//-----------------------------------------------------------------envp_parser
/**
 * parse envp into an array of strings
 * @param mini_data struct where new array of strings is writen
 * @param envp envp given to main
*/
void	parse_array_envp(t_data *mini_data, char **envp);
/**
 * parse envp into a list
 * @param mini_data struct where new array of strings is writen
 * @param envp envp given to main
*/
void	parse_list_envp(t_data *mini_data, char **envp);

//----------------------------------------------------------------------errors
/**
 * write Syntax error near unexpected token `newline' set 258 exit code free
 * token_list and command_list
*/
void	syntax_error_parse(t_state_machine *parser, t_data *mini_data);
/**
 * writes no such file/directory error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	no_file_directory(char **command, t_data *mini);
/**
 * writes command not found, change exit code to 127 and free command
 * @param command array of strings containing information for the errror
 * message
 */
void	no_command(char **command, t_data *mini);
/**
 * writes permission denied error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	permission_denied(char **command, t_data *mini);
/**
 * writes not valid identifier  error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	not_valid_identifier(char **command, t_data *mini);
/**
 * writes too many args error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	too_many_args(char **command, t_data *mini);
/**
 * writes numeric arg required error message, set exit code to 255 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	numeric_arg_required(char **command, t_data *mini);
/**
 * writes not a directory error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void not_directory(char **command, t_data *mini);
/**
 *
 * @param command
 */
void	no_filedir(char *str, char *command, t_data *mini);
void	not_valid_identifier_s(char **command, t_data *mini);
void	not_set(char *command, char *str, t_data *mini);
void	not_directory_cd(char *command, t_data *mini);

//--------------------------------------------------------------------history
void	line_history(t_data *mini_data);

//--------------------------------------------------------i_want_to_break_free
/**
 * frees token list
 * @param tokens pointer to the head of the list to be freed
*/
void	free_token_list(t_tokens **tokens);
/**
 * frees cmd list
 * @param cmd pointer to the head of the list to be freed
*/
void	free_cmd_list(t_commands **cmd);
/**
 * frees pid list
 * @param lst pointer to the head of the list to be freed
*/
void	free_pid_list(t_pid **lst);

//----------------------------------------------------------token_list_actions
/**
 * adds a new token to the list
 * @param tokens list of tokens
 * @param token token to be added
 * @param type type od token (types are described at lexical_analyzer.h)
 * (T_PIPE, T_CHAR, T_SMALL, T_SMALLSAMLL, T_BIG, T_BIGBIG)
 */
void	add_token(t_tokens **tokens, char *token, t_type type);
/**
 * print tokens list
 * @param tokens
 */
void	print_tokens(t_tokens *tokens);
/**
 * check amount of tokens
 * @param tokens pointer to the head of tokens list
 * @return list size
 */
int		find_size(t_tokens *tokens);
/**
 * count amount of heredoc occurences in the token list
 * @param tokens head of token list
 * @return amount of heredoc occurences
 */
int count_heredocs(t_tokens *tokens);

#endif //MINISHELL_UTILS_H
