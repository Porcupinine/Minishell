// ADD HEADER

/* 
	unset: values and attributes of variables and functions
	Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.
	via envp (PATH and SHELL)?? --> look in the shell + the list created by laura
	maybe getenvp then unlink
	and for attributes/var ??
*/

char **update_envp(char **envp, char *arg, int size)
{
	char **new;
	int i;

	new = malloc((size + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (envp[i] && i < size)
	{
		if (ft_strncmp(envp[i], arg, ft_strlen(arg)) == 0)
			free(envp[i]);
		else
			new[i] = envp[i];
		i++;
	}
	new[size] = NULL;
	free(envp); // needed??
	free(arg); // needed??
	return (new);
}

int	size_envp(t_data *mini) // put seperate maybe
{
	int size;

	size = 0;
	while (mini->mini_envp[size])
		size++;
	return(size);
}

static int unset_arg(t_data *mini, char *arg)
{
	char **new;
	char *to_unset;
	int size;

	to_unset = ft_strjoin(arg, "=");
	if (to_unset == NULL)
		return (-1);
	size = size_envp(mini);
	new = update_envp(mini->mini_envp, to_unset, size - 1); // think twice 
	if (to_unset == NULL)
		return (free(to_unset), -1);
	mini->mini_envp = new:
	return (0);
}

int find_envp(t_data *mini, char *arg)
{
	int i;

	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], arg, ft_strlen(arg)) == 0)
			return (i);
		i++;
	}
	return (-1); // meaning not found
}

void	builtin_unset(t_data *mini, char *cmd) 
{
	char **arg;
	int pos;
	int i;
	t_env_args *temp;
	
	arg = ft_split(cmd, " ");
	if (arg == NULL) // as the underscore cannot be unset, but not an error tho for underscore??
		return (ft_exit(errno)); // check this exit tho
	// need to check if only 1 word tho or not?
	i = 1; // skipping the word unset
	while (arg[i])
	{
		if (arg[i] == "_")
			i++; // can't be unset
		pos = find_envp(mini, arg[i]);
		if (pos != -1)
		{
			if (mini->mini_envp[pos])
				unset_arg(data, arg[i]); // could this fail??
		}
		else
			return (builtin_err_unset(arg[i], "not a valid identifier\n"), 1);
		i++;
	}
	free(arg); // or not?? but a recursive free here
	// but doesn't work on directories i believe ..
	// else // search OUR list
	// {
	// 	if (search_args(&mini_data->env_args, arg) != NULL)
	// 	{
	// 		del_args(search_args(&mini_data->env_args, arg)); // check if my logic is correct
	// 		return (0);
	// 	}
	// }
	return (0); // meaning all good
}