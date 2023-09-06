/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:53:54 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 14:35:57 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

bool	check_cmd(char *cmd)
{
	int	i;

	if (cmd[0] == '=')
		return (false);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '='
			&& cmd[i] != '_' && cmd[i] != '$' && cmd[i] != 92
			&& cmd[i] != 34 && cmd[i] != 39)
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_noerror(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0)
		{
			if (cmd[i] != '$' && cmd[i] != 92 && cmd[i] != 34 && cmd[i] != 39)
				return (false);
		}
		i++;
	}
	return (true);
}

int	len_equal(char *cmd)
{
	int	i;

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

void	print_xenv(t_data *mini)
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

char	**add_line_envp(char **envp, char *cmd, t_data *mini)
{
	char	**new;
	int		i;
	int		size;

	size = size_envp(mini) + 1;
	new = ft_calloc_exit((size + 1), sizeof(char *));
	i = 0;
	while (envp[i] && i < size - 1)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	if (cmd[0] == '=')
		return (not_valid_identifier_s(&cmd, mini), free(new), NULL);
	new[i] = ft_strdup(cmd);
	new[size] = NULL;
	free_str(envp);
	return (new);
}
