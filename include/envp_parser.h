/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_parser.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:33:37 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:36:37 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_PARSER_H
# define ENVP_PARSER_H

# include "minishell.h"

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

#endif //ENVP_PARSER_H
