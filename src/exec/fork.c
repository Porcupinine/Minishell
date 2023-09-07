/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 21:58:44 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

static void	dup_close_file(t_data *mini, t_commands *commands)
{
	input_re(commands, mini);
	if (commands->in < 0)
		return (set_exit_code(mini, 1));
	output_re(commands);
	if (commands->out < 0)
		return (set_exit_code(mini, 1));
	if (commands->in != STDIN_FILENO)
	{
		if (dup2(commands->in, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
		close(commands->in);
	}
	if (commands->out != STDOUT_FILENO)
	{
		if (dup2(commands->out, STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
		close(commands->out);
	}
}

static int	exec_last_cmd(t_data *mini, t_commands *commands, int read_end)
{
	pid_t	pid;

	pid = fork();
	ignore_signals();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		return (err_msg("", "fork failed.\n"),
			set_exit_code(mini, 1), -1);
	if (pid == 0)
	{
		unset_signals();
		if (dup2(read_end, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"),
				set_exit_code(mini, 1), exit(1), -1);
		dup_close_file(mini, commands);
		split_args(commands->cmd, mini->mini_envp, mini);
	}
	if (close(read_end) == -1)
		return (err_msg("", "close failed.\n"),
			set_exit_code(mini, 1), exit(1), -1);
	return (pid);
}

void	childchild(t_data *mini, t_commands *commands, \
	int read_end, int *p_fd)
{
	close(p_fd[0]);
	if (dup2(read_end, STDIN_FILENO) == -1)
		return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
		return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	dup_close_file(mini, commands);
	if (mini->exit_code == 1)
		exit(1);
	split_args(commands->cmd, mini->mini_envp, mini);
	close(p_fd[1]);
}

static int	connect_fds(int read_end, int *p_fd)
{
	close(p_fd[1]);
	if (read_end != STDIN_FILENO)
		close(read_end);
	read_end = p_fd[0];
	return (read_end);
}

int	exec_fork(t_data *mini)
{
	pid_t		pid;
	int			p_fd[2];
	int			read_end;
	t_commands	*tmp;

	tmp = mini->commands;
	read_end = 0;
	while (tmp->next)
	{
		if (pipe(p_fd) == -1)
			return (err_msg("", "pipe failed.\n"),
				set_exit_code(mini, 1), 1);
		if (forkfork(mini, tmp, read_end, p_fd) == 1)
			return (1);
		read_end = connect_fds(read_end, p_fd);
		if (read_end == -1)
			return (1);
		tmp = tmp->next;
	}
	pid = exec_last_cmd(mini, tmp, read_end);
	if (pid != -1)
		pid_exit_code(mini, pid);
	return (mini->exit_code);
}
