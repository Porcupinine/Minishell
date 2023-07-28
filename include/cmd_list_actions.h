/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_actions.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:59:17 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 11:59:20 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_CMD_LIST_ACTIONS_H
#define MINISHELL_CMD_LIST_ACTIONS_H

#include "minishell.h"
#include "lexical_analyzer.h"

void add_cmd_node(t_commands **cmd, t_commands *new_cmd);
void add_inout(t_commands **cmd, char *str, enum s_type type);
void print_cmd_list(t_commands *cmd);

#endif //MINISHELL_CMD_LIST_ACTIONS_H
