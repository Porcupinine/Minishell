/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/28 16:01:30 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void child_dup2(t_data *mini, t_commands *commands, int i, int pos)
{
	if (i > 1024)
		err_msg("", "max amount of pipes reached.\n");// NEEDED ?? idk -- error of some sort;
	else
	{
		input_re(mini->commands); // error checking
		output_re(mini->commands); // error checking
		if (i > 1) // if no the first cmd | stored from the prev cmd;
		{
			if (dup2(mini->fd[pos - 1][0], STDIN_FILENO) == -1) // to read from the prev cmd
				err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
		}
		if (i != mini->nb_cmds) // if not the last one
		{
			if (dup2(mini->fd[pos][1], STDOUT_FILENO) == -1) // to write to
				err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
		}
		// if (commands->infiles != NULL)
		if (commands->in != STDIN_FILENO)
		{
			if (dup2(mini->commands->in, STDIN_FILENO) == -1) // to read from the prev cmd
				err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
		}
		// if (commands->outfiles != NULL)
		if (commands->out != STDOUT_FILENO)
		{
			if (dup2(mini->commands->out, STDOUT_FILENO) == -1) // to read from the prev cmd
				err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
		}
		close(mini->fd[pos][1]); // is this correct??
		close(mini->fd[pos][0]); // not this right?
		close_fds(mini);
		split_args(commands->cmd, mini->mini_envp, mini);
		// mini->fd[pos][0] || store for next cmd to read
	}
}

void	run_one_cmd(t_data *mini)
{
	input_re(mini->commands); // error checking
	output_re(mini->commands); // error checking
	if (mini->commands->in != STDIN_FILENO)
	{
		if (dup2(mini->commands->in, STDIN_FILENO) == -1) // to read from the prev cmd
			err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	}
	if (mini->commands->out != STDOUT_FILENO)
	{
		if (dup2(mini->commands->out, STDOUT_FILENO) == -1) // to read from the prev cmd
			err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
	}
	// if (in_file != STDIN_FILENO)
	// 	close(in_file); // this one needed tho??
	// if (out_file != STDOUT_FILENO)
	// 	close(out_file);
	//close_pipe(mini->fd, mini->nb_cmds); // needed again here??
	split_args(mini->commands->cmd, mini->mini_envp, mini);
}

// OLD
// void	run_one_cmd(int in_file, int out_file, t_data *mini)
// {
// 	if (dup2(in_file, STDIN_FILENO) == -1)
// 		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
// 	if (dup2(out_file, STDOUT_FILENO) == -1)
// 		err_msg("", "dup2 failed.\n"); // check -- exit(EXIT_FAILURE);
// 	if (in_file != STDIN_FILENO)
// 		close(in_file); // this one needed tho??
// 	if (out_file != STDOUT_FILENO)
// 		close(out_file);
// 	close_pipe(mini->fd, mini->nb_cmds); // needed again here??
// 	split_args(mini->commands->cmd, mini->mini_envp, mini);
// }