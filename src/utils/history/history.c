/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:50:47 by laura         #+#    #+#                 */
/*   Updated: 2023/09/06 00:18:36 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "unistd.h"
#include "../../Lib42/include/libft.h"

int	test_isspace(char*str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		if (ft_strchr(ISSPACE, str[count]) == 0)
			return (0);
		count++;
	}
	return (1);
}

void	line_history(t_data *mini_data)
{
	if (mini_data->command_line == NULL)
	{
		free_envp_array(mini_data->mini_envp);
		free(mini_data);
		mini_data = NULL;
		write(1, "exit\n", 5);
		exit(0);
	}
	if (mini_data->command_line)
	{
		add_history(mini_data->command_line);
	}
}
