/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:56:37 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/31 16:21:24 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void	free_fd(int **fd, int nb_cmds)
{
	int	nb;
	int	i;

	nb = nb_cmds;
	i = 0;
	while (i < nb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	set_exit_code(t_data *mini, int code)
{
	mini->exit_code = code;
}

int	size_envp(t_data *mini)
{
	int	size;

	size = 0;
	while (mini->mini_envp[size])
		size++;
	return (size);
}

int	not_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int find_path(char **envp)
{
	int	i;
	int j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	j = 0;
	while (envp[j])
		j++;
	if (i == j)
		return (-1);
	return (i);
}
