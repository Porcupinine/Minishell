/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/01 17:07:10 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

int	exec_fork_onecmd(t_data *mini)
{
	pid_t	pid;

	pid = fork();
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
	waitpid(pid, &mini->exit_code, 0);
	if (WIFEXITED(mini->exit_code))
		mini->exit_code = WEXITSTATUS(mini->exit_code);
	if (WIFSIGNALED(mini->exit_code))
		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
	return (mini->exit_code);
}

int	exec_fork(t_data *mini, int nb_cmds)
{
	pid_t		pid;
	int			i;
	int			pos;
	t_commands	*tmp;

	tmp = mini->commands;
	i = 1;
	pos = 0;
	while (i <= nb_cmds)
	{
		pid = fork();
		pid_lstadd_back(&mini->process, pid);
		if (pid == -1)
			return (err_msg("", "fork failed.\n"),
				set_exit_code(mini, 1), 1);
		if (pid == 0)
		{
			unset_signals();
			child_dup2(mini, tmp, i, pos); // because what happens when it returns here with an error
		}
		if (i != nb_cmds)
			tmp = tmp->next;
		i++;
		pos++;
	}
	close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	waitpid(pid, &mini->exit_code, 0);
	if (WIFEXITED(mini->exit_code))
		mini->exit_code = WEXITSTATUS(mini->exit_code);
	if (WIFSIGNALED(mini->exit_code))
		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
	return (mini->exit_code);
}
