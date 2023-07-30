/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:11:06 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/28 15:12:48 by domi             ###   ########.fr       */
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

void	builtin_pwd(t_data *mini_data)
{
	char *pwd_path;
	char *pwd;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (ft_exit(errno)); // check this exit tho
	pwd = ft_calloc((ft_strlen(pwd_path) + 2), sizeof(char)); // for null term + newline
	if (pwd == NULL)
		return (ft_exit(errno)); // check this exit tho
	ft_memmove(pwd, pwd_path, ft_strlen(pwd_path));
	pwd[len] = '\n';
	ft_putstr_fd(pwd, mini->commands->out);
	free(pwd_path);
	free(pwd);
	return (0);
}
