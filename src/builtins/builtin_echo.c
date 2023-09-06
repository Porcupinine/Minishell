/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 16:21:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include "../../include/lexical_analyzer.h"

static void	write_echo(int i, char **cmd)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

static void	echo_n(char **cmd, int j, size_t i)
{
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "-", 1) == 0)
		{
			i = 1;
			while (cmd[j] && cmd[j][i] == 'n')
				i++;
		}
		if (ft_strlen(cmd[j]) != i)
			break ;
		j++;
	}
	i = j;
	write_echo(j, cmd);
}

int	builtin_echo(t_data *mini, char **cmd)
{
	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		echo_n(cmd, 1, 0);
		set_exit_code(mini, 0);
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
		write_echo(1, cmd);
		write(1, "\n", 1);
		set_exit_code(mini, 0);
	}
	else
		no_command(cmd, mini);
	return (mini->exit_code);
}
