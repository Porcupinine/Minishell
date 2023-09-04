/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/04 14:43:46 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include "../../include/lexical_analyzer.h"

static void	write_echo(int i, char **cmd, t_data *mini)
{
	char	*tmp;

	tmp = NULL;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '\'') != 0 || ft_strchr(cmd[i], '"') != 0)
		{
			tmp = cmd[i];
			cmd[i] = remove_quotes(cmd[i]);
			free(tmp);
			tmp = NULL;
		}
		ft_putstr_fd(cmd[i], mini->commands->out);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', mini->commands->out);
		i++;
	}
}

static void	echo_n(t_data *mini, char **cmd, int j, size_t i)
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
//	while (cmd[i])
//	{
//		cmd[i] = expand_dollar(cmd[i], mini);
//		i++;
//	}
	write_echo(j, cmd, mini);
}

int	builtin_echo(t_data *mini, char **cmd)
{
	int	i;

	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		echo_n(mini, cmd, 1, 0);
		set_exit_code(mini, 0);
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
		i = 1;
//		while (cmd[i])
//		{
//			if (ft_strchr(cmd[i], '\'') == 0)
//				cmd[i] = expand_dollar(cmd[i], mini);
//			i++;
//		}
		write_echo(1, cmd, mini);
		write(mini->commands->out, "\n", 1);
		set_exit_code(mini, 0);
	}
	else
		no_command(cmd, mini);
	return (mini->exit_code);
}
