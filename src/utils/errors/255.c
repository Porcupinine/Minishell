
/* ************************************************************************** */
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

void numeric_arg_required(t_data *mini_data)
{
	//TODO how?
//	printf();
	g_exit_code = 255;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL; //TODO do we have kids too kill?
	return_prompt();
}