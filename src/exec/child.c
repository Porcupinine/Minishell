/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/17 10:49:50 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static void	child_start(int fd_w[], int in_file, t_commands *commands, t_data *mini)
{
	printf("FIRST CHILD? fd_w == %d    in_file == %d\n", fd_w[1], in_file);
	if (dup2(in_file, STDIN_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	//close(fd_w[0]);
	// if (in_file != STDIN_FILENO) // or what should be the rule here??
	// 	close(in_file);
	//close_pipe(commands->fd, mini->nb_cmds);
	split_args(commands->cmd, mini->mini_envp, mini);
}

static void	child_last(int fd_r[], int out_file, t_commands *commands, t_data *mini)
{
	printf("LAST CHILD?\n");
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	if (dup2(out_file, STDOUT_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	close(fd_r[1]);
	if (out_file != STDOUT_FILENO) // or what should be the rule here??
		close(out_file);
	close_pipe(mini->fd, mini->nb_cmds);
	split_args(commands->cmd, mini->mini_envp, mini);
}

static void	child_middle(int fd_r[], int fd_w[], t_commands *commands, t_data *mini)
{
	printf("MIDDLE CHILD?\n");
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	close(fd_w[0]);
	close(fd_r[1]);
	close_pipe(mini->fd, mini->nb_cmds);
	split_args(commands->cmd, mini->mini_envp, mini); 
}

void	which_child(t_data *mini, t_commands *commands, int i, int pos)
{
	printf("HERE IN CHILD?\n, i == %d pos == %d nb_cmd == %d \n", i, pos, mini->nb_cmds);
	if (i == 1 && pos == 0)
		child_start(mini->fd[pos], commands->in, commands, mini); 
	else if (i == mini->nb_cmds)
		child_last(mini->fd[pos - 1], commands->out, commands, mini);
	else
	{
	printf("END OF CHILD\n");
		if (i <= 1024) // think its fine here as you never know if something might break -- max amount pipes
			child_middle(mini->fd[pos - 1], mini->fd[pos], commands, mini);
		else
			err_msg("", "max amount of pipes reached.\n");// idk -- error of some sort;
	}
}

// NEW VERSION
// void child_dup2(t_data *mini, t_commands *commands, int i, int pos)
// {
// 	if (i > 1024)
// 		err_msg("", "max amount of pipes reached.\n");// idk -- error of some sort;


	
// }

void	run_one_cmd(int in_file, int out_file, t_data *mini)
{
	if (dup2(in_file, STDIN_FILENO) == -1) 
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	if (dup2(out_file, STDOUT_FILENO) == -1)
		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	if (in_file != STDIN_FILENO)
		close(in_file); // this one needed tho??
	if (out_file != STDOUT_FILENO)
		close(out_file);
	close_pipe(mini->fd, mini->nb_cmds); // needed again here??
	split_args(mini->commands->cmd, mini->mini_envp, mini);
}
