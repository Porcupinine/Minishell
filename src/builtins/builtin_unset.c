/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:32:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/15 16:00:19 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

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
			new[i] = ft_strdup(envp[i]); // what if it returns NULL here??
		i++;
	}
	new[size] = NULL;
	free(envp); // needed??
	// free(arg); // needed??
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
	mini->mini_envp = new;
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

int	builtin_unset(t_data *mini, char **arg) // or not an int??
{
	int pos;
	int i;

	// need to check if only 1 word tho or not?
	i = 1; // skipping the word unset
	while (arg[i])
	{
		//if (arg[i][0] == '_')
		if (ft_strncmp(arg[i], "_", 1) == 0)
			i++; // can't be unset
		pos = find_envp(mini, arg[i]);
		if (pos != -1)
		{
			if (mini->mini_envp[pos])
				unset_arg(mini, arg[i]); // could this fail??
		}
		else
			return (builtin_err2("unset", arg[i], "not a valid identifier\n"), 1);
		i++;
	}
	return (0); // meaning all good
}