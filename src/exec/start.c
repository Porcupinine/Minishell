/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/17 19:45:46 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/I_want_to_break_free.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

extern int g_exit_code;

void close_fds(t_data *mini)
{
	// printf("HERE? %d %d\n", mini->commands->in, mini->commands->out);
	printf("HERE (in close_fds)?\n");
	if (mini->commands->in != 0)
		close(mini->commands->in);
	if (mini->commands->out != 1)
		close(mini->commands->out);
	if (access("tmp_file", F_OK) == 0) // does this work?
		unlink("tmp_file");
}

static int	execute_pipe(t_data *mini, int nb_cmds)
{
	pid_t	pid;
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	while (i <= nb_cmds)
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini->commands); // error checking 
		pid = fork();
		pid_lstadd_back(&mini->process, pid);
		if (pid == -1)
			ft_error("Fork failed.\n");
		if (pid == 0)
			which_child(mini, mini->commands, i, pos);
		i++;
		pos++;
		mini->commands = mini->commands->next;
	}
	close_pipe(mini->fd, mini->nb_cmds);
	close_fds(mini);
	free_fd(mini->fd, mini->nb_cmds);
	waitpid(pid, &mini->status, 0);
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
	if (WIFSIGNALED(mini->status))  // check
		mini->status = WTERMSIG(mini->status);  // check
	return (0); // check
}

static int	**open_pipes(t_data *mini)
{
	int		**fd;
	int		nb;
	int		i;

	nb = mini->nb_cmds;
	fd = (int **)malloc((nb) * sizeof(int *));
	if (fd == NULL)
		ft_error("Malloc failed.\n"); // check
	i = 0;
	while (i < nb)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pipe(fd[i]) < 0)
			ft_error("Pipe failed.\n"); // check
		i++;
	}
	return (fd);
}

void	close_pipe(int **fd, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

static void multiple_cmd(t_data *mini)
{
	mini->fd = open_pipes(mini); // level needs to be changes else fd only stored on the first cmd
	execute_pipe(mini, mini->nb_cmds); // check if a success
	// if (execute_pipe(mini, mini->nb_cmds) == errno) // check
	// 	return (errno); // check what to return here, maybe just 1
	free_pid_list(&mini->process);
	mini->process = NULL;
}

static void one_cmd(t_data *mini)
{
	char **command;

	command = ft_split(mini->commands->cmd, ' ');
	if (!command)
		ft_error("Malloc failed\n");
	input_re(mini->commands, mini); // error checking
	output_re(mini->commands); // error checking 
	mini->fd = open_pipes(mini);
	if (mini->fd == NULL)
		err_msg("", "pipe opening failed.\n"); // check
	if (check_builtins(command, mini) == 1) // so not a builtin
	{
		free_str(command);
		exec_fork_onecmd(mini);
		free_pid_list(&mini->process);
		mini->process = NULL;
	}
	else 
	{
		free_str(command);
		run_one_cmd(mini->commands->in, mini->commands->out, mini);
		close_pipe(mini->fd, mini->nb_cmds);
		free_fd(mini->fd, mini->nb_cmds);
		close_fds(mini);
	}
}

int	start(t_data *mini)
{
	mini->nb_cmds = lst_size(mini->commands);
	if (mini->nb_cmds == 1 && !mini->commands->cmd) 
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini->commands); // error checking 
		close_fds(mini);
	}
	else if (mini->nb_cmds == 1)
		one_cmd(mini);
	else
	{
		multiple_cmd(mini);
		// mini->fd = open_pipes(mini);
		// if (mini->fd == NULL)
		// 	err_msg("", "pipe opening failed.\n"); // check, might be double now
		// if (execute_pipe(mini, mini->nb_cmds) == errno) // check
		// 	return (errno); // check what to return here, maybe just 1
		// free_pid_list(&mini->process);
		// mini->process = NULL;
	}
	free_cmd_list(&mini->commands);
	mini->commands = NULL;
	return (0);  // right?? because if anything it will have errored in the input/output ft
}


/*
	TO WORK ON:
		-- fork even with one command --> DONE
		-- rework the whole child process to create one for all
		-- go through all the builtins
			-- ++ send double pointer to cd and exit
			-- rework cd (its all broke..)
			-- add mini to exit
		-- adapt the location to find $?
		-- check and change all the error functions
		-- add the right exit_code everywhere
			-- rm g_exit_code
	
*/