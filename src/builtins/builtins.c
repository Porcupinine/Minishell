/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 12:09:51 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	builtins(char **cmd, char *str, t_data *mini)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(mini, cmd, str);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		builtin_cd(mini, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		builtin_pwd(mini);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		builtin_export(mini, cmd, str);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		builtin_unset(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		builtin_env(mini, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		builtin_exit(mini, cmd);
	else
		return (1);
	return (0);
}

int	check_builtins(char **cmd)
{
	if (!cmd[0])
		return (1);
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (0);
	return (1);
}
