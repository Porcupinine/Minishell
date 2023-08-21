/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/21 16:36:51 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/I_want_to_break_free.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

int	exec_fork_onecmd(t_data *mini)
{
	pid_t	pid;

	pid = fork();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		ft_error("Fork failed.\n"); // check errno ft_error exits the program 
	if (pid == 0)
		run_one_cmd(mini);
    close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	//close_fds(mini);
	waitpid(pid, &mini->status, 0);
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
	if (WIFSIGNALED(mini->status))  // check
		mini->status = 128 + WTERMSIG(mini->status);  // check
	return (0); // check
}

int	exec_fork(t_data *mini, int nb_cmds)
{
	pid_t	pid;
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	while (i <= nb_cmds)
	{
		pid = fork();
		pid_lstadd_back(&mini->process, pid);
		if (pid == -1)
			ft_error("Fork failed.\n");
		if (pid == 0)
			child_dup2(mini, mini->commands, i, pos);
		if (i != nb_cmds)
			mini->commands = mini->commands->next;
		i++;
		pos++;
	}
	close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	//close_fds(mini); // then maybe this one not needed if exits/execve
	waitpid(pid, &mini->status, 0);
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
	if (WIFSIGNALED(mini->status))  // check
		mini->status = 128 + WTERMSIG(mini->status);  // check
	return (0); // check
}

// OLD
// int	exec_fork_onecmd(t_data *mini)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	pid_lstadd_back(&mini->process, pid);
// 	if (pid == -1)
// 		ft_error("Fork failed.\n"); // check errno ft_error exits the program 
// 	if (pid == 0)
// 		run_one_cmd(mini->commands->in, mini->commands->out, mini);
//     close_pipe(mini->fd, mini->nb_cmds);
// 	free_fd(mini->fd, mini->nb_cmds);
// 	close_fds(mini);
// 	waitpid(pid, &mini->status, 0); // or w/ mini->process->pid ??
// 	if (WIFEXITED(mini->status)) // check
// 		mini->status = WEXITSTATUS(mini->status); // check
// 	return (0); // check
// }