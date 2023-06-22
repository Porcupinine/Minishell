/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:22:07 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/22 16:11:49 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/pipes.h"
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
		if (access(the_path, F_OK) == 0) // needs to be X_OK perhaps ??
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

char	*split_args(char *argv, char **envp)
{
	char	**command;
	char	*path_to_cmd;
	char	**paths;
	int		i;

	i = 0;
	if (*envp == NULL)
		exit(127);
	command = split_command(argv);
	paths = ft_split(envp[find_path(envp)] + 5, ':');
	if (!paths)
		cmd_not_found(command);
	path_to_cmd = join_path(command[0], paths, 0);
	if (!path_to_cmd)
		cmd_not_found(command);
	if (path_to_cmd != NULL && command != NULL)
		execve(path_to_cmd, command, envp);
	free(path_to_cmd);
	free_str(command);
	exit(EXIT_FAILURE);
}
