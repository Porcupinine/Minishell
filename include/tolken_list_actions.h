/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tolken_list_actions.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:31:44 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:32:28 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOLKEN_LIST_ACTIONS_H
# define TOLKEN_LIST_ACTIONS_H

# include "minishell.h"
# include "lexical_analyzer.h"

void	add_token(t_tokens **tokens, char *token, t_type type);
void	print_tokens(t_tokens *tokens);
int find_size(t_tokens *tokens);

#endif //TOLKEN_LIST_ACTIONS_H
