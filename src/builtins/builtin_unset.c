/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 12:32:10 by dmaessen      #+#    #+#                 */
/*   Updated: 2023/09/06 00:23:16 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static bool	is_exact_match(char *to_compare, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (to_compare[i] == '=')
			break ;
		if (arg[i] != to_compare[i])
			return (false);
		i++;
	}
	return (true);
}

char	**update_envp(char **envp, char *arg, int size)
{
	char	**new;
	int		i;
	int		j;

	new = ft_calloc_exit((size + 1), sizeof(char *));
	i = 0;
	j = 0;
	while (envp[i] && i < size + 1)
	{
		if (ft_strncmp(envp[i], arg, ft_strlen(arg)) == 0
			&& is_exact_match(arg, envp[i]) == true)
			i++;
		else
		{
			new[j] = ft_strdup(envp[i]);
			j++;
			i++;
		}
	}
	new[size] = NULL;
	return (new);
}

static int	unset_arg(t_data *mini, char *arg)
{
	char	**new;
	char	*to_unset;
	int		size;

	to_unset = ft_strjoin(arg, "=");
	size = size_envp(mini);
	new = update_envp(mini->mini_envp, to_unset, size - 1);
	free(to_unset);
	if (new == NULL)
		return (-1);
	free_str(mini->mini_envp);
	mini->mini_envp = new;
	return (set_exit_code(mini, 0), 0);
}

int	find_envp(t_data *mini, char *arg)
{
	int	i;

	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], arg, ft_strlen(arg)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	builtin_unset(t_data *mini, char **arg)
{
	int	pos;
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_strncmp(arg[i], "_\0", 2) == 0)
			i++;
		else
		{
			pos = find_envp(mini, arg[i]);
			if (pos != -1)
			{
				if (mini->mini_envp[pos])
					if (unset_arg(mini, arg[i]) == -1)
						return (error_msg("failed to update envp\n", mini), -1);
			}
			else if (not_alphanum(arg[i]) != 0)
				not_valid_identifier(arg, mini);
			i++;
		}
	}
	return (mini->exit_code);
}
