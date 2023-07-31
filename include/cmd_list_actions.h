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

/**
 * adds a command node to the command list
 * @param cmd pointer to the head of the list of commands
 * @param new_cmd new command node
 */
void add_cmd_node(t_commands **cmd, t_commands *new_cmd);
/**
 * add infiles and outfiles to the list inside the new command node
 * @param cmd command node
 * @param str name of the file
 * @param type type of redirection
 */
void add_inout(t_commands **cmd, char *str, enum s_type type);
/**
 * print the list of commands with list of infiles and outfiles if they exist
 * @param cmd pointer to the head of the command list
 */
void print_cmd_list(t_commands *cmd);

#endif //MINISHELL_CMD_LIST_ACTIONS_H
