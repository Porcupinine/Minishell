/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 12:13:54 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include "../../include/lexical_analyzer.h"

static void	write_echo(int i, char **cmd, int fd)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', fd);
		i++;
	}
}

static void	echo_n(char **cmd, int j, size_t i, int fd)
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
	write_echo(j, cmd, fd);
}

int	builtin_echo(t_data *mini, char **cmd, char *str)
{
	int fd;
	int	i;

	if (mini->commands->out == 0)
		fd = 1;
	else
		fd = mini->commands->out;
	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		echo_n(cmd, 1, 0, fd);
		set_exit_code(mini, 0);
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
		//write_echo(1, cmd, fd);
		i = 4;
		while (str[++i])
			ft_putchar_fd(str[i], fd);
		write(fd, "\n", 1);
		set_exit_code(mini, 0);
	}
	else
		no_command(cmd, mini);
	return (mini->exit_code);
}
