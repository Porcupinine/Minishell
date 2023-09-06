/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:13:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 22:04:45 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

int	builtin_env(t_data *mini, char **cmd)
{
	int	i;

	if (cmd[1] != NULL)
	{
		no_filedir("env", cmd[1], mini);
		return (mini->exit_code);
	}
	if (ft_strncmp(cmd[0], "env\0", 4) != 0)
	{
		no_command(cmd, mini);
		return (mini->exit_code);
	}
	i = 0;
	while (mini->mini_envp[i])
	{
		ft_putstr_fd(mini->mini_envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	set_exit_code(mini, 0);
	return (mini->exit_code);
}
