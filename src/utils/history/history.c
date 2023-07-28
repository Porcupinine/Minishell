/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:50:47 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 11:50:51 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdlib.h>
#include "../../include/minishell.h"

void	line_history(t_data *mini_data)
{
	if (mini_data->command_line == NULL)
		exit(0);
	if (mini_data->command_line)
		add_history(mini_data->command_line);

}
