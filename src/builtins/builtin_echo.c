/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 14:46:57 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

/*
	should it also handle echo $?  ??
	example to deal with the $ARG/$PATH expantion: printf("PATH : %s\n", getenv("PATH"));
	// one extra else if in case non-accepted flags, or does laura handle upfront?
	// for both handle the $ or not ?? think so
	// check if quotes
		// if yes check if they are closed
		// else needs to read from stdin
*/
int	builtin_echo(t_data *mini, char *cmd)
{
	int i;
	
	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		// check if there is a $ still in there or not? LAURA
		i = 9;
		while (mini->commands->cmd[i])
		{
			ft_putstr_fd(mini->commands->cmd[i], mini->commands->out);
			i++;
		}
	}
	else
	{
		i = 6;
		while (mini->commands->cmd[i])
		{
			ft_putstr_fd(mini->commands->cmd[i], mini->commands->out);
			i++;
		}
		write(mini->commands->out, "\n", 1);
	}
	return (0); // check
}
