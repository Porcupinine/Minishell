/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:22:16 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/01 13:16:26 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

void	close_fds(t_data *mini)
{
	if (mini->commands->in != 0)
		close(mini->commands->in);
	if (mini->commands->out != 1)
		close(mini->commands->out);
}

int	**open_pipes(t_data *mini)
{
	int		**fd;
	int		nb;
	int		i;

	nb = mini->nb_cmds;
	fd = ft_calloc_exit(nb, sizeof(int *));
	i = 0;
	while (i < nb)
	{
		fd[i] = ft_calloc_exit(2, sizeof(int));
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pipe(fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (fd);
}

void	close_pipe(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
