/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:43:14 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 17:39:08 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"
#include <sys/wait.h>

void	run_one_cmd(t_data *mini)
{
	input_re(mini->commands, mini);
	output_re(mini->commands, mini);
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

int	exec_fork_onecmd(t_data *mini)
{
	pid_t	pid;

	pid = fork();
	ignore_signals();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		return (err_msg("", "fork failed.\n"),
			set_exit_code(mini, 1), 1);
	if (pid == 0)
	{
		unset_signals();
		run_one_cmd(mini);
	}
	close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	pid_exit_code(mini, pid);
	return (mini->exit_code);
}

int	forkfork(t_data *mini, t_commands *commands, \
	int read_end, int *p_fd)
{
	pid_t		pid;

	pid = fork();
	ignore_signals();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		return (err_msg("", "fork failed.\n"),
			set_exit_code(mini, 1), 1);
	if (pid == 0)
	{
		unset_signals();
		childchild(mini, commands, read_end, p_fd);
	}
	return (0);
}

void	pid_exit_code(t_data *mini, pid_t pid)
{
	waitpid(pid, &mini->exit_code, 0);
	if (WIFEXITED(mini->exit_code))
		mini->exit_code = WEXITSTATUS(mini->exit_code);
	else if (WIFSIGNALED(mini->exit_code))
	{
		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
		if (mini->exit_code == 131)
			write(1, "^\\Quit: 3\n", 10);
	}
	while (1)
		if (wait(NULL) == -1)
			break ;
}
