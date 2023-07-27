/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/27 13:25:30 by dmaessen         ###   ########.fr       */
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

void ft_exit(int error)
{
	strerror(error);
	exit(error);
}

/* 
	unset: values and attributes of variables and functions
	Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.
	via envp (PATH and SHELL)?? --> look in the shell + the list created by laura
	maybe getenvp then unlink
	and for attributes/var ??
*/
static t_env_args *search_args(t_env_args *env_args, char *arg)
{
	while (env_args->next != NULL)
	{
		if (env_args->name == arg)
			return (&env_args); 
		env_args = env_args->next;
	}
	return (NULL);
}

static void del_args(t_env_args *env_args)
{
	t_env_args *temp;
	
	temp = env_args->next;
	env_args->name = env_args->next->name;
	env_args = temp;
	free(temp);
}

void	builtin_unset(t_data *mini_data) 
{
	char *arg;
	char *path;
	t_env_args *temp;
	
	arg = ft_substr(mini_data->tolkens->str, ft_strlen("unset "), ft_strlen(mini_data->tolkens->str)); // str in a certain position tho..
	// ABOVE IS WRONG JUST TAKE NEXT ARG IN LIST AFTER 'UNSET'
	if (arg == NULL || arg == "_") // as the underscore cannot be unset, but not an error tho for underscore??
		return (ft_exit(errno)); // check this exit tho
	// need to check if only 1 word tho or not?
	path = getenv(arg);
	if (path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (unlink(path) == 0) // search the ones given by shell
		return (0);
	// but doesn't work on directories i believe ..
	else // search OUR list
	{
		if (search_args(&mini_data->env_args, arg) != NULL)
		{
			del_args(search_args(&mini_data->env_args, arg)); // check if my logic is correct
			return (0);
		}
	}
	return (ft_exit(errno)); // meaning not found
}

void	builtin_exit(t_data *mini_data)
{
	// int status;

	// TO REWORK, exit can hold an int (exit 1), alpha (not sure if accepted) and something else dk
	
	printf("exit\n");
	// do we also maybe need to use rl_clear_history ??
	exit(0); 
	// check if we need to free things before closing the program
	// or with another status, but which one then??
}

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
