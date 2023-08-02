/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/02 12:54:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static void	child_start(int fd_w[], int in_file, t_commands *commands, t_data *mini)
{
	if (dup2(in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_w[0]);
	close(in_file);
	close_pipe(commands->fd, commands->nb_cmds);
	split_args(commands->cmd, mini->mini_envp, mini);
}

static void	child_last(int fd_r[], int out_file, t_commands *commands, t_data *mini) // pos to loop to the right node before sending to split_arg
{
	// int i;

	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(out_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_r[1]);
	close(out_file);
	close_pipe(commands->fd, commands->nb_cmds);
	// i = -1;
	// while (++i < pos && mini->commands->next != NULL)
	// 	mini->commands = mini->commands->next;
	split_args(commands->cmd, mini->mini_envp, mini); // check if it gave the right pos in the end
}

static void	child_middle(int fd_r[], int fd_w[], t_commands *commands, t_data *mini) // pos to loop to the right node before sending to split_arg
{
	int i;

	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_w[0]);
	close(fd_r[1]);
	close_pipe(commands->fd, commands->nb_cmds);
	// i = -1;
	// while (++i < pos && mini->commands->next != NULL)
	// 	mini->commands = mini->commands->next;
	split_args(commands->cmd, mini->mini_envp, mini); // check if it gave the right pos in the end
}

void	which_child(t_data *mini, t_commands *commands, int i, int pos)
{
	if (i == 1 && pos == 0)
		child_start(commands->fd[pos], commands->in, commands, mini); 
	else if (i == commands->nb_cmds)
		child_last(commands->fd[pos - 1], commands->out, commands, mini);
	else
	{
		if (i <= 1024) // think its fine here as you never know if something might break -- max amount pipes
			child_middle(commands->fd[pos - 1], commands->fd[pos], commands, mini);
		// else
			// idk -- error of some sort;
	}
}

void	run_one_cmd(int in_file, int out_file, t_data *mini)
{
	if (dup2(in_file, STDIN_FILENO) == -1) 
		exit(EXIT_FAILURE); // check
	if (dup2(out_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(in_file);
	close(out_file);
	close_pipe(mini->commands->fd, mini->commands->nb_cmds); // needed again here??
	split_args(mini->commands->cmd, mini->mini_envp, mini);
}
