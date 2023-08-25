/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:13:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/25 13:34:42 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

int	builtin_env(t_data *mini, char **cmd)
{
	int i;

	if (cmd[1] != NULL) // make sense??
	{
		// too_many_args(cmd); // CANNOT REPLICATE THE TO MANY ARGS ANYMORE
		// return (1); // check on this
		no_filedir("env", cmd[1]);
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
