/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/02 18:05:16 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static void	child_dup(t_data *mini, t_commands *commands, int i, int pos)
{
	if (i > 1 && commands->in == STDIN_FILENO)  
	{
		if (dup2(mini->fd[pos - 1][0], STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (i != mini->nb_cmds && commands->out == STDOUT_FILENO)
	{
		if (dup2(mini->fd[pos][1], STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (commands->in != STDIN_FILENO)
	{
		if (dup2(commands->in, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (commands->out != STDOUT_FILENO)
	{
		if (dup2(commands->out, STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	printf("gets to the dup??\n");
}

void	child_dup2(t_data *mini, t_commands *commands, int i, int pos)
{
	// if (i != mini->nb_cmds) // new -- needed?
	// 	close(mini->fd[pos][0]);
	if (commands->in > 0) // new -- needed?
		close(commands->in);
	input_re(commands, mini);
	if (commands->in < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	output_re(commands);
	if (commands->out < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	child_dup(mini, commands, i, pos);
	if (mini->exit_code == 1)
	{
		exit (1); // added exit
		return ;
	}
	if (i != mini->nb_cmds)  // new -- needed?
		close(mini->fd[pos][1]);
	if (i > 1) // new -- needed?
		close(mini->fd[pos - 1][0]); // or -1
	close_fds(mini);
	split_args(commands->cmd, mini->mini_envp, mini);
}

void	run_one_cmd(t_data *mini)
{
	input_re(mini->commands, mini);
	output_re(mini->commands);
	if (mini->commands->out < 0 || mini->commands->in < 0)
	{
		exit(1);
		return ;
	}
	if (mini->commands->in != STDIN_FILENO)
	{
		if (dup2(mini->commands->in, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (mini->commands->out != STDOUT_FILENO)
	{
		if (dup2(mini->commands->out, STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	split_args(mini->commands->cmd, mini->mini_envp, mini);
}


// fd0 -- read
// fd1 -- write


// OLD 
// static void	child_dup(t_data *mini, t_commands *commands, int i, int pos)
// {
// 	if (i > 1 && commands->in == STDIN_FILENO)  
// 	{
// 		if (dup2(mini->fd[pos - 1][0], STDIN_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	if (i != mini->nb_cmds && commands->out == STDOUT_FILENO)
// 	{
// 		if (dup2(mini->fd[pos][1], STDOUT_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	if (commands->in != STDIN_FILENO)
// 	{
// 		if (dup2(commands->in, STDIN_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	if (commands->out != STDOUT_FILENO)
// 	{
// 		if (dup2(commands->out, STDOUT_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	printf("gets to the dup??\n");
// }

// void	child_dup2(t_data *mini, t_commands *commands, int i, int pos)
// {
// 	// if (i != mini->nb_cmds) // new -- needed?
// 	// 	close(mini->fd[pos][0]);
// 	if (commands->in > 0) // new -- needed?
// 		close(commands->in);
// 	input_re(commands, mini);
// 	if (commands->in < 0)
// 		return (set_exit_code(mini, 1), exit(1)); // added exit
// 	output_re(commands);
// 	if (commands->out < 0)
// 		return (set_exit_code(mini, 1), exit(1)); // added exit
// 	child_dup(mini, commands, i, pos);
// 	if (mini->exit_code == 1)
// 	{
// 		exit (1); // added exit
// 		return ;
// 	}
// 	if (i != mini->nb_cmds)  // new -- needed?
// 		close(mini->fd[pos][1]);
// 	if (i > 1) // new -- needed?
// 		close(mini->fd[pos - 1][0]); // or -1
// 	close_fds(mini);
// 	split_args(commands->cmd, mini->mini_envp, mini);
// }

// void	run_one_cmd(t_data *mini)
// {
// 	input_re(mini->commands, mini);
// 	output_re(mini->commands);
// 	if (mini->commands->out < 0 || mini->commands->in < 0)
// 	{
// 		exit(1);
// 		return ;
// 	}
// 	if (mini->commands->in != STDIN_FILENO)
// 	{
// 		if (dup2(mini->commands->in, STDIN_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	if (mini->commands->out != STDOUT_FILENO)
// 	{
// 		if (dup2(mini->commands->out, STDOUT_FILENO) == -1)
// 			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
// 	}
// 	split_args(mini->commands->cmd, mini->mini_envp, mini);
// }


// // fd0 -- read
// // fd1 -- write