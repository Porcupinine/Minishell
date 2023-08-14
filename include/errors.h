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
 * 
*/
void	syntax_error_parse(t_state_machine *parser, t_data *mini_data);
void	no_file_directory(char **command);
void	no_command(char **command);
void	permission_denied(char **command);
void	not_valid_identifier(char **command);
void	too_many_args(char **command);
void	numeric_arg_required(char **command);


#endif //MINISHELL_ERRORS_H
