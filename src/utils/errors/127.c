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
#include <unistd.h>
#include "../../Lib42/include/libft.h"
#include "../../include/exec.h"

extern int g_exit_code;

void no_command(char **command, t_data *mini_data)
{
//	printf("%: Command not found\n", command);
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	g_exit_code = 127;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL;//TODO do we have kids too kill?
	free_str(command);
	return_prompt();
}
