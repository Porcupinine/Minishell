/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:50:47 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:09:33 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "unistd.h"

void	line_history(t_data *mini_data)
{
	if (mini_data->command_line == NULL) //TODO check if erno is 0 for readline
	{
		free_envp_array(mini_data->mini_envp);
		free(mini_data->command_line);
		mini_data->command_line = NULL;
		free(mini_data);
		mini_data = NULL;
		write(1, "exit\n", 5);
		exit(0);
	}
	if (mini_data->command_line)
		add_history(mini_data->command_line);
}
