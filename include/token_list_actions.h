/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_actions.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:31:44 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 12:00:05 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_ACTIONS_H
# define TOKEN_LIST_ACTIONS_H

# include "minishell.h"
# include "lexical_analyzer.h"

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

#endif //TOKEN_LIST_ACTIONS_H
