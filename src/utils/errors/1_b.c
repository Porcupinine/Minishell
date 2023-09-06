/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_b.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:30:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 14:30:16 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"

void	permission_denied(char **command, t_data *mini)
{
	mini->exit_code = 1;
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	if (command[1] != NULL)
	{
		write(2, ": ", 2);
		write(2, command[1], ft_strlen(command[1]));
	}
	else
		mini->exit_code = 126;
	write(2, ": ", 2);
	write(2, "permission denied\n", 18);
}

void	too_many_args(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, "too many arguments\n", 19);
	mini->exit_code = 1;
}

void	not_directory(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "Not a directory\n", 17);
	mini->exit_code = 1;
}

void	not_set(char *command, char *str, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	mini->exit_code = 1;
}

void	not_directory_cd(char *command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, "cd: ", 4);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, "Not a directory\n", 17);
	mini->exit_code = 1;
}
