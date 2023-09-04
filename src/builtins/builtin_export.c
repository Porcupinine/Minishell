/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 14:39:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static void	print_xenv(t_data *mini)
{
	int	i;
	int	j;

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
	set_exit_code(mini, 0);
}

static char	**add_line_envp(char **envp, char *cmd, int size, t_data *mini)
{
	char	**new;
	int		i;

	new = ft_calloc_exit((size + 1), sizeof(char *));
	i = 0;
	while (envp[i] && i < size - 1)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
//	cmd = expand_dollar(cmd, mini);
	if (cmd[0] == '=')
		return (not_valid_identifier_s(&cmd, mini), free(new), NULL);
	new[i] = ft_strdup(cmd);
	new[size] = NULL;
	free(envp);
	return (new);
}

static int	go_export(t_data *mini, char *cmd)
{
	char	*name;
	int		i;
	char	**new;
	int		size;

	name = ft_substr(cmd, 0, len_equal(cmd));
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], name,
				ft_strlen(name) - 1) == 0)
		{
			mini->mini_envp[i] = ft_strdup("");
			mini->mini_envp[i] = ft_strjoin(mini->mini_envp[i], cmd);
			return (free(name), set_exit_code(mini, 0), 0);
		}
		i++;
	}
	free(name);
	size = size_envp(mini);
	new = add_line_envp(mini->mini_envp, cmd, size + 1, mini);
	if (new == NULL)
		return (mini->exit_code);
	mini->mini_envp = new;
	return (set_exit_code(mini, 0), 0);
}

int	builtin_export(t_data *mini, char **cmd)
{
	int	i;

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
			return (not_valid_identifier(cmd, mini), 1);
	}
	return (mini->exit_code);
}
