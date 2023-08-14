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

void no_file_directory(char *cmd, char*file, t_data *mini_data)
{
	printf("%s: %s: No such file or directory\n", cmd, file);
	g_exit_code = 1;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL; //TODO do we have kids too kill?
	return_prompt();
}

void not_valid_identifier(char *cmd, char *ident, t_data *mini_data)
{
	printf("minisomething: %s: ´%s´: not a valid identifier\n", cmd, ident);
	g_exit_code = 1;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL; //TODO do we have kids too kill?
	return_prompt();
}

void permission_denied(char *cmd, char *folder, t_data *mini_data)
{
	printf("minisomething: %s: %s: permission denied\n", cmd, folder);
	g_exit_code = 1;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL; //TODO do we have kids too kill?
	return_prompt();
}

void too_many_args(t_data *mini_data)
{
	//TODO can see error?
//	printf();
	g_exit_code = 1;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL; //TODO do we have kids too kill?
	return_prompt();
}