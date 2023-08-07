/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/07 17:31:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

/*
	using export should add the mentionned variable to envp
	(not the same as our local arg list)

	// export a variable
	// do we support the = something ??
	// access envp
	// open with write rights and add a line for it
*/
// deal with the below
// eg. just "export" and its printing the whole env with 'declare -x' in front of each line
// eg. "export =hey" --> minishell: export: '=hey': not a valid identifier
// eg. "export hey" --> does nothing

// NEW VERSION
static void print_xenv(t_data *mini)
{
	int i;
	int j;

	i = 0;
	while (mini->mini_envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (mini->mini_envp[i][j])
		{
			if (mini->mini_envp[i][j] == '=')
				ft_putstr_fd("=\"", 1);
			else
				ft_putchar_fd(mini->mini_envp[i][j], 1);
			j++;
		}
		ft_putstr_fd("\"\n", 2);
		i++;
	}
}

static bool check_cmd(char *cmd)
{
	int i;

	if (cmd[0] == '=')
		return (false);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '=' && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int len_equal(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

static char **add_line_envp(char **envp, char *cmd, int size)
{
	char **new;
	int i;

	new = malloc((size + 1) * sizeof(char *));
	if (new == NULL)
		return (ft_error("Malloc failed.\n"), NULL);
	i = 0;
	while (envp[i] && i < size - 1)
	{
		new[i] = ft_strdup(envp[i]); // what if it returns NULL here??
		i++;
	}
	new[i] = ft_strdup(cmd); // what if it returns NULL here??
	new[size] = NULL;
	free(envp); // needed?? recursively??
	return (new);
}

static int go_export(t_data *mini, char *cmd)
{
	char *name;
	int i;
	char **new;
	int size;

	i = len_equal(cmd);
	name = ft_substr(cmd, 0, i);
	if (name == NULL)
		return (ft_error("Malloc failed.\n"), 1); // check
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], name, ft_strlen(name) - 1) == 0) // skipping the \0 ??
		{
			ft_strlcpy(mini->mini_envp[i], cmd, ft_strlen(cmd)); // or +1?
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	size = size_envp(mini);
	new = add_line_envp(mini->mini_envp, cmd, size + 1);
	mini->mini_envp = new;
	return (0);
}

int builtin_export(t_data *mini, char **cmd)
{
	int i;

	if (!cmd[1])
		print_xenv(mini);
	i = 1;
	while (cmd[i])
	{
		if (check_cmd(cmd[i]) == true)
			go_export(mini, cmd[i]);
		else
			return (builtin_err2(cmd[0], cmd[i], "not a valid identifier\n") , 1); // exit code should be 1 
		i++;
	}
	return (0);
}