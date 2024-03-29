/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:11 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 16:00:31 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include <stdio.h>

static void	modif_env(t_data *mini, char *cmd)
{
	int		i;
	char	*res;
	int		count;

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
				mini->mini_envp[i] = ft_strjoin("SHLVL=", ft_itoa(count));
				free(res);
				break ;
			}
			i++;
		}
	}
}

static char	*first_command(char **command)
{
	char	*cmd;

	cmd = ft_strdup(command[0]);
	if (cmd[0] == '/')
	{
		cmd = ft_strrchr(cmd, '/');
		if (ft_strrchr(cmd, '/') == NULL)
			return (NULL);
	}
	return (cmd);
}

static char	*join_path(char **command, char **paths, int i, t_data *mini)
{
	char	*the_path;
	char	*cmd;
	char	*tmp;

	cmd = first_command(command);
	if (cmd == NULL)
		return (NULL);
	while (paths[i])
	{
		the_path = ft_strjoin(paths[i], "/");
		tmp = the_path;
		the_path = ft_strjoin(the_path, cmd);
		free(tmp);
		if (!the_path)
			return (free(the_path), NULL);
		if (access(the_path, F_OK) == 0)
		{
			if (access(the_path, X_OK) != 0)
				return (permission_denied(command, mini), exit(126), NULL);
			return (free_str(paths), the_path);
		}
		free(the_path);
		i++;
	}
	return (free_str(paths), free(cmd), NULL);
}

static void	no_pathtocmd(char *path_to_cmd, t_data *mini, \
	char **command, char **envp)
{
	if (!path_to_cmd)
	{
		modif_env(mini, command[0]);
		execve(command[0], &command[0], envp);
		no_command(command, mini);
		exit(mini->exit_code);
	}
}

char	*split_args(char *cmd, char **envp, t_data *mini)
{
	char	**command;
	char	*path_to_cmd;
	char	**paths;

	command = ft_split(cmd, ' ');
	if (builtins(command, cmd, mini) == 1)
	{
		if (*envp == NULL)
			return (ft_error("Envp not found\n"), NULL);
		if (find_path(envp) <= 0)
			no_pathtocmd(NULL, mini, command, envp);
		paths = ft_split(envp[find_path(envp)] + 5, ':');
		if (!paths)
			return (no_filedir("minishell", command[0], mini),
				exit(mini->exit_code), NULL);
		path_to_cmd = join_path(command, paths, 0, mini);
		no_pathtocmd(path_to_cmd, mini, command, envp);
		if (path_to_cmd != NULL && command != NULL)
			execve(path_to_cmd, command, envp);
		free(path_to_cmd);
	}
	if (mini->nb_cmds != 1)
		exit(0);
	return (free_str(command), NULL);
}
