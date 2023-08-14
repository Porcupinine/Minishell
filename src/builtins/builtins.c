/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/14 14:13:48 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	builtins(char **cmd, t_data *mini)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(mini, cmd);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		builtin_cd(mini, *cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		builtin_pwd(mini);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		builtin_export(mini, cmd);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		builtin_unset(mini, cmd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		builtin_env(mini, cmd);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		builtin_exit(*cmd);
	else
		return (1); // meaning not found
	return (0);
}
