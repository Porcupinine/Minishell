/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/03 18:08:25 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

static void	reset_cmdlist(t_data *mini)
{
	free_cmd_list(&mini->commands);
	mini->commands = NULL;
}

static void	multiple_cmd(t_data *mini)
{
	// mini->fd = open_pipes(mini);
	// if (mini->fd == NULL)
	// 	return (err_msg("", "pipe opening failed.\n"),
	// 		set_exit_code(mini, 1));
	exec_fork(mini); // what do we do when dup2 fails??
	free_pid_list(&mini->process);
	mini->process = NULL;
}

static void	one_cmd(t_data *mini)
{
	char	**command;

	command = ft_split(mini->commands->cmd, ' ');
	if (check_builtins(command) == 1)
	{
		mini->fd = open_pipes(mini);
		if (mini->fd == NULL)
			return (free(command), err_msg("", "pipe opening failed.\n"),
				set_exit_code(mini, 1));
		free_str(command);
		exec_fork_onecmd(mini);
		free_pid_list(&mini->process);
		mini->process = NULL;
	}
	else
	{
		free_str(command);
		input_re(mini->commands, mini);
		output_re(mini->commands);
		if (mini->commands->out < 0 || mini->commands->in < 0)
			return (set_exit_code(mini, 1), close_fds(mini));
		split_args(mini->commands->cmd, mini->mini_envp, mini);
		close_fds(mini);
	}
}

int	start(t_data *mini)
{
	mini->nb_cmds = lst_size(mini->commands);
	if (mini->nb_cmds == 1 && ft_strlen(mini->commands->cmd) == 0)
	{
		input_re(mini->commands, mini);
		if (mini->commands->in < 0)
			return (reset_cmdlist(mini), set_exit_code(mini, 1), 1);
		output_re(mini->commands);
		if (mini->commands->out < 0)
			return (reset_cmdlist(mini), set_exit_code(mini, 1), 1);
		close_fds(mini);
	}
	else if (mini->nb_cmds == 1)
		one_cmd(mini);
	else
		multiple_cmd(mini);
	free_cmd_list(&mini->commands);
	mini->commands = NULL;
	if (access("tmp_file", F_OK) == 0)
		unlink("tmp_file");
	return (mini->exit_code);
}
