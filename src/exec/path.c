/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:11 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/29 14:16:53 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include <stdio.h>

static void modif_env(t_data *mini, char *cmd)
{
	int i;
	char *res;
	int count;
	
	i = 0;
	if (ft_strncmp(cmd, "./minishell", 11) == 0)
	{
		while (mini->mini_envp[i])
		{
			if (ft_strncmp(mini->mini_envp[i], "SHLVL=", 6) == 0)
			{
				res = ft_strtrim(mini->mini_envp[i], "SHLVL=");
				count = ft_atoi(res);
				count += 1;
				mini->mini_envp[i] = ft_strjoin("SHLVL=", ft_itoa(count)); // or itoa here?
				free(res);
				break ;
			}
			i++;
		}
	}
}

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

static char	*join_path(char **command, char **paths, int i, t_data *mini)
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
				permission_denied(command, mini);
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
			no_filedir("minishell", command[0], mini);
			exit(mini->exit_code);
		}
		path_to_cmd = join_path(command, paths, 0, mini);
		if (!path_to_cmd)
		{
			if (!path_to_cmd && ft_strncmp(command[0], "./", 2) == 0)
			{
				modif_env(mini, command[0]);
				execve(command[0], &command[0], envp);
			}
			else
			{
				no_command(command, mini);
				exit(mini->exit_code);
			}
		}
		if (path_to_cmd != NULL && command != NULL)
			execve(path_to_cmd, command, envp);
		free(path_to_cmd);
	}
	free_str(command);
	if (mini->nb_cmds != 1)
		exit (0);
	return (0);
}
