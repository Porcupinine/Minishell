// ADD 42 HEADER

#include "minishell.h"

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

char	*split_args(char *cmd, char **envp, t_data *mini)
{
	char	**command;
	char	*path_to_cmd;
	char	**paths;
	int		i;

	i = 0;
	command = ft_split(cmd, ' '); // need to check if there is a remaining $ to replce in there?
	if (!command)
		return (NULL); // check
	// check here is command == buitlin else the below
	if (builtins(command[0], mini) == 1) // meaning not a builtin
	{
		if (*envp == NULL)
			exit(127); // check 
		paths = ft_split(envp[find_path(envp)] + 5, ':');
		if (!paths)
			cmd_not_found(command); // check
		path_to_cmd = join_path(command[0], paths, 0);
		if (!path_to_cmd)
			cmd_not_found(command); // check
		if (path_to_cmd != NULL && command != NULL)
			execve(path_to_cmd, command, envp);
		free(path_to_cmd); // check -- means execve failed
		free_str(command); // check -- means execve failed
		exit(EXIT_FAILURE); // check -- means execve failed
	}
	// and if a builtin?? something else needed? or things to free??
	exit(EXIT_SUCCESS); // or not?
}
