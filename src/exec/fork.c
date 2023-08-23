/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/17 10:37:08 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

// int	exec_fork(t_data *mini, int nb_cmds)
// {
// 	pid_t	pid;
// 	int		i;
// 	int 	pos;

// 	i = 1;
// 	pos = 0;
// 	while (i <= nb_cmds)
// 	{
// 		input_re(mini->commands, mini); // error checking
// 		output_re(mini->commands); // error checking 
// 		pid = fork();
// 		pid_lstadd_back(&mini->process, pid);
// 		if (pid == -1)
// 			ft_error("Fork failed.\n"); // check errno ft_error exits the program 
// 		if (pid == 0)
// 			which_child(mini, mini->commands, i, pos);
// 		i++;
// 		pos++;
// 		mini->commands = mini->commands->next;
// 	}
// 	close_pipe(mini->fd, mini->nb_cmds);
// 	free_fd(mini->fd, mini->nb_cmds);
// 	close_fds(mini);
// 	waitpid(pid, &mini->commands->status, 0); // or w/ mini->process->pid ??
// 	if (WIFEXITED(mini->commands->status))
// 		return (WEXITSTATUS(mini->commands->status)); // check
// 	return (0); // check
// }

int	exec_fork_onecmd(t_data *mini)
{
	pid_t	pid;

	pid = fork();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		ft_error("Fork failed.\n"); // check errno ft_error exits the program 
	if (pid == 0)
		run_one_cmd(mini->commands->in, mini->commands->out, mini);
    close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	close_fds(mini);
	waitpid(pid, &mini->status, 0); // or w/ mini->process->pid ??
	if (WIFEXITED(mini->status)) // check
		mini->status = WEXITSTATUS(mini->status); // check
	return (0); // check
}