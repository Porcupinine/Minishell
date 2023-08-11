/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   I_want_to_break_free.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:27:40 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:32:00 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_WANT_TO_BREAK_FREE_H
# define I_WANT_TO_BREAK_FREE_H

# include "minishell.h"
# include "lexical_analyzer.h"

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

#endif //I_WANT_TO_BREAK_FREE_H
