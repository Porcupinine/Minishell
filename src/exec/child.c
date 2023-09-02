/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/01 22:32:24 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static void	child_dup(t_data *mini, t_commands *commands, int i, int pos)
{
	if (i > 1 && commands->in == STDIN_FILENO) // added here && commands->in == STDIN_FILENO
	{
		if (dup2(mini->fd[pos - 1][0], STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (i != mini->nb_cmds && commands->out == STDOUT_FILENO) // added here && commands->out == STDOUT_FILENO
	{
		if (dup2(mini->fd[pos][1], STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (commands->in != STDIN_FILENO)
	{
		// printtf("IN DUP2 IN %d OUT %d\n", commands->in, commands->out);
		if (dup2(commands->in, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
	if (commands->out != STDOUT_FILENO)
	{
		if (dup2(commands->out, STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	}
}

void	child_dup2(t_data *mini, t_commands *commands, int i, int pos)
{
	// if (i != mini->nb_cmds) // new -- needed?
	// 	close(mini->fd[pos][0]); // ou pas - 1 jsp
	input_re(commands, mini);
	if (commands->in < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	output_re(commands);
	if (commands->out < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	printf("IN DUP2 IN %d OUT %d\n", commands->in, commands->out);
	child_dup(mini, commands, i, pos);
	if (mini->exit_code == 1)
	{
		exit (1); // added exit
		return ;
	}
	// if (mini->commands->in >= 0) // new -- needed?
	// 	close(mini->commands->in);
	// if (i != mini->nb_cmds)  // new -- needed?
	close(mini->fd[pos][1]);
	// if (i > 1) // new -- needed?
	close(mini->fd[pos][0]);
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