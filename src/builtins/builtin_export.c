/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/25 14:56:58 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

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
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '=' && cmd[i] != '_' && cmd[i] != '$')
			return (false);
		i++;
	}
	return (true);
}

static bool is_valid_noerror(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0)
		{
			if (cmd[i] != '$')
				return (false);
		}
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

static char **add_line_envp(char **envp, char *cmd, int size, t_data *mini)
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
	cmd = expand_dollar(cmd, mini);
	if (cmd[0] == '=')
		return (not_valid_identifier_s(&cmd), free(new), NULL);
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
		ft_error("Malloc failed.\n"); // check
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
	new = add_line_envp(mini->mini_envp, cmd, size + 1, mini);
	if (new == NULL)
		return (1);
	mini->mini_envp = new;
	return (0);
}

int builtin_export(t_data *mini, char **cmd)
{
	int i;

	if (!cmd[1] && ft_strlen(cmd[0]) == 6)
		print_xenv(mini);
	if (!cmd[1] && ft_strlen(cmd[0]) > 6)
		no_command(cmd, mini);
	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '=') == NULL && is_valid_noerror(cmd[i]) == true)
			i++;
		else if (check_cmd(cmd[i]) == true)
		{
			go_export(mini, cmd[i]);
			i++;
		}
		else
			return (not_valid_identifier(cmd), 1); // exit code should be 1 
	}
	return (0);
}