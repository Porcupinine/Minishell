/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/21 16:13:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>

static int	execute_pipe(t_data *mini)
{
	pid_t	process;
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	// mini->commands->process = malloc(sizeof(t_pid) * mini->commands->nb_cmds); // CHECK w Laura
	while (i <= mini->commands->nb_cmds)
	{
		// if (i == 1)
		// {
		// 	pid_lstnew(mini->commands->process->pid); // is this correct
		// 	mini->commands->process->pid = fork(); // or just "process" here ??
		// }
		process = fork();
		if (process == -1)
			return (1); // check
		if (process == 0)
			which_child(mini, i, pos);
		i++;
		pos++;
	}
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	free_fd(mini->commands->fd, mini->commands->nb_cmds);
	close(mini->commands->in); // only if needed/present
	close(mini->commands->out); // only if needed/present
	if (mini->commands->infiles->file->type == heredoc)
		unlink("tmp_file");
	waitpid(process, &mini->commands->status, 0);
	if (WIFEXITED(mini->commands->status)) // check
		exit(WEXITSTATUS(mini->commands->status)); // check
	return (0); // check
}

static int	**open_pipes(t_data *mini)
{
	int		**fd;
	int		nb;
	int		i;

	nb = mini->commands->nb_cmds;
	fd = (int **)malloc((nb) * sizeof(int *));
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
			return (NULL);
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

int	start(t_data *mini)
{
	input_re(mini); // error checking ++ if no in file then ..??
	output_re(mini); // error checking
	
	mini->commands->nb_cmds = lst_size(mini->commands);
	if (mini->commands->nb_cmds == 0)
	{
		// could just an outfile? and infile??
	}
	else if (mini->commands->nb_cmds == 1)
	{
		
	}
	else
	{
		mini->commands->fd = open_pipes(mini);
		if (mini->commands->fd == NULL)
			exit(EXIT_FAILURE); // check if correct exit
		if (execute_pipe(mini) == 1) // if no in/out file will break the logic here
			exit(EXIT_FAILURE); // check if correct exit
	}
		
    
	// other version needed without in and out files OR could we make a rule depending on < << >> > ??


	// don't forget to close files
	// and delete temp_file if it was there created by heredoc
	
	// pid's need to be freed
}


/*
	i left off at:
		-- start.c
			execute_pipe line 22 ++ 27: what to do with pids? how to create the list? LAURA??
		-- utils.c
			check on the t_pid ones, if correct and needed??
		-- builtins.c
			go through them to adapt now we know the structure

	QUESTION:
		-- what would be the best approach for the pids?? storing them in a struct or not??
		-- (LAURA) in echo should i still filter though the str see if there is a $ in there??
	
	all error handling to go through
	
			
*/