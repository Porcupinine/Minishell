/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 16:40:10 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include "../../include/lexical_analyzer.h"

static int	echo_n(char **cmd, int j, size_t i)
{
	int	count;
	int	a;

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
	if (cmd[j] == NULL)
		j -= 1;
	a = 0;
	count = 0;
	while (a < j)
	{
		count += ft_strlen(cmd[a]) + 1;
		a++;
	}
	return (count);
}

static int	set_fd(t_data *mini)
{
	if (mini->commands->out == 0)
		return (1);
	else
		return (mini->commands->out);
}

int	builtin_echo(t_data *mini, char **cmd, char *str)
{
	int	fd;
	int	i;

	fd = set_fd(mini);
	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0)
	{
		i = echo_n(cmd, 1, 0) - 1;
		while (str[++i])
			ft_putchar_fd(str[i], fd);
		set_exit_code(mini, 0);
	}
	else if (ft_strlen(cmd[0]) == 4)
	{
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
