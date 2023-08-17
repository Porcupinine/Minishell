/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:32:27 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:33:04 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"
# include "lexical_analyzer.h"

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
void	no_file_directory(char **command);
/**
 * writes command not found, change exit code to 127 and free command
 * @param command array of strings containing information for the errror
 * message
 */
void	no_command(char **command);
/**
 * writes permission denied error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	permission_denied(char **command);
/**
 * writes not valid identifier  error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	not_valid_identifier(char **command);
/**
 * writes too many args error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	too_many_args(char **command);
/**
 * writes numeric arg required error message, set exit code to 255 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void	numeric_arg_required(char **command);
/**
 * writes not a directory error message, set exit code to 1 and free
 * command array
 * @param command array of strings containing information for the errror
 * message
 */
void not_directory(char **command);


#endif //MINISHELL_ERRORS_H
