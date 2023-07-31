/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 17:01:48 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static void	child_start(int fd_w[], int in_file, t_data *mini) // pointer needed??
{
	if (dup2(in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_w[0]);
	close(in_file);
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	split_args(mini->commands->cmd, mini->mini_envp, mini);
}

static void	child_last(int fd_r[], int out_file, t_data *mini, int pos) // pos to loop to the right node before sending to split_arg
{
	int i;

	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(out_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_r[1]);
	close(out_file);
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	i = -1;
	while (++i < pos && mini->commands->next != NULL)
		mini->commands = mini->commands->next;
	split_args(mini->commands->cmd, mini->mini_envp, mini); // check if it gave the right pos in the end
}

static void	child_middle(int fd_r[], int fd_w[], t_data *mini, int pos) // pos to loop to the right node before sending to split_arg
{
	int i;

	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_w[0]);
	close(fd_r[1]);
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	i = -1;
	while (++i < pos && mini->commands->next != NULL)
		mini->commands = mini->commands->next;
	split_args(mini->commands->cmd, mini->mini_envp, mini); // check if it gave the right pos in the end
}

void	which_child(t_data *mini, int i, int pos)
{
	if (i == 1 && pos == 0)
		child_start(mini->commands->fd[pos], mini->commands->in, mini); 
	else if (i == mini->commands->nb_cmds)
		child_last(mini->commands->fd[pos - 1], mini->commands->out, mini, pos);
	else
	{
		if (i <= 1024) // think its fine here as you never know if something might break -- max amount pipes
			child_middle(mini->commands->fd[pos - 1], mini->commands->fd[pos], mini, pos);
		// else
			// idk -- error of some sort;
	}
}
