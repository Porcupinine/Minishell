/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:11 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/07 17:07:51 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static int	find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

static char	*join_path(char *command, char **paths, int i)
{
	char	*the_path;

	if (command[0] == '/')
	{
		command = ft_strrchr(command, '/');
		if (ft_strrchr(command, '/') == NULL)
			return (0);
	}
	while (paths[i])
	{
		the_path = ft_strjoin(paths[i], "/");
		the_path = ft_strjoin(the_path, command);
		if (!the_path)
			return (free(the_path), NULL);
		if (access(the_path, F_OK) != 0 || access(the_path, X_OK) != 0)
		{
			err_msg(command, "Permission denied\n");
			//return ; // check as should: exit(127);
		}
		if (access(the_path, X_OK) == 0)
		{
			free_str(paths);
			return (the_path);
		}
		free(the_path);
		i++;
	}
	free_str(paths);
	return (0);
}

char	*split_args(char *cmd, char **envp, t_data *mini)
{
	char	**command;
	char	*path_to_cmd;
	char	**paths;

	command = ft_split(cmd, ' ');
	if (!command)
		return (ft_error("Malloc failed\n"), NULL); // check
	if (builtins(command, mini) == 1) // meaning not a builtin
	{
		if (*envp == NULL)
			exit(127); // TODO check as we don't want to exit
		paths = ft_split(envp[find_path(envp)] + 5, ':');
		if (!paths)
			err_cmd_not_found(command); // exit should be with // exit(127);
		path_to_cmd = join_path(command[0], paths, 0);
		if (!path_to_cmd)
			err_cmd_not_found(command); // exit should be with // exit(127);
		if (path_to_cmd != NULL && command != NULL)
			execve(path_to_cmd, command, envp);
		free(path_to_cmd);
		free_str(command);
		// throw an error, to check
	}
	free_str(command);
	return (0); // check, what happens if something goes wrong in builtins??
}
