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

#endif //MINISHELL_ERRORS_H
