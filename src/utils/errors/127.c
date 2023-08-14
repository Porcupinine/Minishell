git /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1.c                                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:04:28 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:04:30 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/I_want_to_break_free.h"

// _: _: no such file or directory

extern int g_exit_code;

void no_command(char *cmd, t_data *mini_data)
{
	printf("%: Command not found\n", cmd);
	g_exit_code = 127;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL;//TODO do we have kids too kill?
	return_prompt();
}