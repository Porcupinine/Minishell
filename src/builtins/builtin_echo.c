/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/11 22:48:23 by domi             ###   ########.fr       */
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
int	builtin_echo(t_data *mini, char **cmd)
{
	int i;

	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		i = 0;
		while (cmd[i])
		{
			cmd[i] = expand_dollar(cmd[i], mini);
			i++;
		}
		i = 8;
		while (mini->commands->cmd[i])
		{
			ft_putchar_fd(mini->commands->cmd[i], mini->commands->out);
			i++;
		}
		return (0); // check
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
		i = 0;
		while (cmd[i])
		{
			cmd[i] = expand_dollar(cmd[i], mini);
			i++;
		}
		i = 5;
		while (mini->commands->cmd[i]) //TODO echo by itself should print newline but breaks here
		{
			ft_putchar_fd(mini->commands->cmd[i], mini->commands->out);
			i++;
		}
		write(mini->commands->out, "\n", 1);
		return (0); // check
	}
	else
		no_command(cmd);
	return (127); // check
}
