/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:13:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/29 16:26:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

int	builtin_env(t_data *mini, char **cmd)
{
	int	i;

	if (cmd[1] != NULL)
	{
		no_filedir("env", cmd[1], mini);
		return (127);
	}
	i = 0;
	while (mini->mini_envp[i])
	{
		ft_putstr_fd(mini->mini_envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
