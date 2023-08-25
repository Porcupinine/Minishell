/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:11 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/25 13:36:41 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include <stdio.h>

static int	find_path(char **envp)
{
	int	i;
	int j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	j = 0;
	while (envp[j])
		j++;
	if (i == j)
		return (0);
	return (i);
}

static char	*join_path(char **command, char **paths, int i)
{
	char	*the_path;
	char	*cmd;

	cmd = ft_strdup(command[0]);
	if (cmd[0] == '/')
	{
		cmd = ft_strrchr(cmd, '/');
		if (ft_strrchr(cmd, '/') == NULL)
			return (0);
	}
	while (paths[i])
	{
		the_path = ft_strjoin(paths[i], "/");
		the_path = ft_strjoin(the_path, cmd);
		if (!the_path)
			return (free(the_path), NULL);
		// if (access(the_path, F_OK) != 0 || access(the_path, X_OK) != 0)
		if (access(the_path, F_OK) == 0)
		{
			if (access(the_path, X_OK) != 0)
			{
				permission_denied(command);
				//return ; // check as should: exit(127);
			}
			free_str(paths);
			return (the_path);
		}
		free(the_path);
		i++;
	}
	free_str(paths);
	free(cmd);
	return (0);
}

char	*split_args(char *cmd, char **envp, t_data *mini)
{
	char	**command;
	char	*path_to_cmd;
	char	**paths;

	command = ft_split(cmd, ' ');
	if (!command)
		ft_error("Malloc failed\n");
	if (builtins(command, mini) == 1)
	{
		if (*envp == NULL)
			exit(127); // TODO check as we don't want to exit
		paths = ft_split(envp[find_path(envp)] + 5, ':');
		if (!paths || find_path(envp) == 0)
		{
			no_filedir("unset", command[]);
			// no_command(command, mini); // exit with // exit(127);
			exit(0); 
		}
		path_to_cmd = join_path(command, paths, 0);
		if (!path_to_cmd)
			no_command(command, mini); // exit with // exit(127);
		if (path_to_cmd != NULL && command != NULL)
			execve(path_to_cmd, command, envp);
		//printf("%s", path_to_cmd);
		free(path_to_cmd);
		// throw an error, to check
	}
	free_str(command);
	if (mini->nb_cmds != 1)
		exit (0);
	return (0);
}
