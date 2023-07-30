/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:13:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/28 12:20:40 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

int	builtin_env(t_data *mini, char *cmd)
{
	int i;

	if (ft_strlen(cmd) > 3)
		return (builtin_err(cmd[0], "too many arguments\n"), 1); // check on this
	i = 0;
	while (mini->mini_envp[i])
	{
		ft_putstr_fd(mini->mini_envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
