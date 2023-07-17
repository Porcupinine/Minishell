/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_list_actions.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:36:31 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:36:58 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_LIST_ACTIONS_H
# define ARG_LIST_ACTIONS_H

# include "minishell.h"

void	add_arg(t_env_args *args, char *name, char *value);

#endif //MINISHELL_ARG_LIST_ACTIONS_H
