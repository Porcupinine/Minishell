/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/25 13:14:12 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/errors.h"

 extern int g_exit_code;
/*
	should it also handle echo $?  ??
	example to deal with the $ARG/$PATH expantion: printf("PATH : %s\n", getenv("PATH"));
	// one extra else if in case non-accepted flags, or does laura handle upfront?
	// for both handle the $ or not ?? think so
	// check if quotes
		// if yes check if they are closed
		// else needs to read from stdin
*/

static void echo_n(t_data *mini, char **cmd, int j, size_t i)
{
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "-n", 2) == 0)
		{
			i = 2;
			while (cmd[j] && cmd[j][i] == 'n')
				i++;
		}
		if (ft_strlen(cmd[j]) != i)
			break ;
		j++;
	}
	i = j;
	while (cmd[i])
	{
		cmd[i] = expand_dollar(cmd[i], mini);
		i++;
	}
	i = j;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], mini->commands->out);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', mini->commands->out);
		i++;
	}
}

int	builtin_echo(t_data *mini, char **cmd)
{
	int i;

	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		echo_n(mini, cmd, 1, 0);
		return (0); // check
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
		i = 1;
		while (cmd[i])
		{
			cmd[i] = expand_dollar(cmd[i], mini);
			i++;
		}
		i = 1;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], mini->commands->out);
			if (cmd[i + 1] != NULL)
				ft_putchar_fd(' ', mini->commands->out);
			i++;
		}
		write(mini->commands->out, "\n", 1);
		return (0); // check
	}
	else
		no_command(cmd, mini);
	return (127); // check
}
