/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/30 21:08:37 by domi             ###   ########.fr       */
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

int	builtins(char **cmd, t_data *mini)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0) //
		builtin_echo(mini, *cmd); // with this pointer does it send it as a str completly???
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		builtin_cd(mini, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		builtin_pwd(envp);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		builtin_export();
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		builtin_unset();
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		builtin_env(mini_data);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		builtin_exit(mini_data);
		// can't we just use the "real exit" function here, and leave the shell?
	else
		return (1); // meaning not found
	return (0);
}
