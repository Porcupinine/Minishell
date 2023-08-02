/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/02 13:02:08 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static int	execute_pipe(t_data *mini)
{
	pid_t	process;
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	while (i <= mini->commands->nb_cmds)
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini->commands); // error checking 
		process = fork();
		pid_lstadd_back(mini->process->pid, process);
		if (process == -1)
			return (ft_error("Fork failed.\n"), errno); // check errno
		if (process == 0)
			which_child(mini, mini->commands, i, pos);
		i++;
		pos++;
		mini->commands = mini->commands->next;
	}
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	free_fd(mini->commands->fd, mini->commands->nb_cmds);
	close(mini->commands->in);
	close(mini->commands->out);
	// if (mini->commands->infiles->file->type == "HEREDOC") // check -- change for int
	if (access("tmp_file", F_OK) == 0) // does this work? apply to the rest if yes
		unlink("tmp_file");
	waitpid(process, &mini->commands->status, 0); // or w/ mini->process->pid ??
	if (WIFEXITED(mini->commands->status))
		return (WEXITSTATUS(mini->commands->status)); // check
	return (0); // check
}

static int	**open_pipes(t_data *mini)
{
	int		**fd;
	int		nb;
	int		i;

	nb = mini->commands->nb_cmds;
	fd = (int **)malloc((nb) * sizeof(int *));
	if (fd == NULL)
		return (ft_error("Malloc failed.\n"), NULL); // check
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
			return (ft_error("Pipe failed.\n"), NULL); // check -- needs to be on stderr
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

static void close_fds(t_data *mini)
{
	if (mini->commands->in != NULL)
		close(mini->commands->in);
	if (mini->commands->out != NULL)
		close(mini->commands->out);
	// if (mini->commands->infiles->file->type == "HEREDOC") // check -- change for int
	if (access("tmp_file", F_OK) == 0) // does this work? apply to the rest if yes
		unlink("tmp_file");
}

int	start(t_data *mini)
{
	// input_re(mini); // error checking
	// output_re(mini); // error checking 
	mini->commands->nb_cmds = lst_size(mini->commands);
	if (mini->commands->nb_cmds == 0)
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini); // error checking 
		close_fds(mini);
	}
	else if (mini->commands->nb_cmds == 1)
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini); // error checking 
		mini->commands->fd = open_pipes(mini);
		if (mini->commands->fd == NULL)
			err_msg("", "pipe opening failed.\n"); // check
		run_one_cmd(mini->commands->in, mini->commands->out, mini);
		close_pipe(mini->commands->fd, mini->commands->nb_cmds);
		free_fd(mini->commands->fd, mini->commands->nb_cmds);
		close_fds(mini);
	}
	else
	{
		mini->commands->fd = open_pipes(mini);
		if (mini->commands->fd == NULL)
			err_msg("", "pipe opening failed.\n"); // check, might be double now
		if (execute_pipe(mini) == errno) // check
			return (errno); // check what to return here, maybe just 1
		// pid's need to be freed??
	}
	return (0);  // right?? because if anything it will have errored in the input/output ft
}


/*
	i left off at:
		-- input_op.c --> CHECK ON THIS THING HERE
			—- check if NULL checks needed when in file == NULL;
		-- output_op.c --> TO DO
			explicitly tell how to open, without the expansion
		-- builtins.c --> WORKING ON THIS HERE
			the builtinds cmd is already split so double pointer, make use of it no...
			builtin_echo.c: find a good way to retreive and add/expand the $ARG 
			builtin_export.c: so it also works with multiple ARGs to be set
			builtin_unset.c: could just rm the line, free it and shift up the rest??
		-- error.c
			write something for all the errors
			++ go throgh all error handling to go through
		-- start.c 
			HEREDOC CHECK: --> THINK THAT'S SOLVED NOW, check
				(limiter = hey)
					hallo\
					hey
					hey (only exists here and it gives back hallohey so rm the \) --> THINK THAT'S SOLVED NOW, DON'T HANDLE ACTUALLY
				(limiter = he"y")
					it will disregard the quotes and just use hey as limiter --> THINK THAT'S SOLVED NOW

	QUESTION:
		-- what would be the best approach for the pids?? storing them in a struct or not?? PROBABLY 
		-- (LAURA) in echo should i still filter though the str see if there is a $ in there?? YES 
	
	
			
*/