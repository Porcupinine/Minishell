/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/20 16:55:09 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_pipe(t_data *mini)
{
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	mini->commands->process = malloc(sizeof(t_pid) * mini->commands->nb_cmds);
	if (!p.ph)
		return (ft_exit("Error: malloc.\n"));
	while (i <= mini->commands->nb_cmds)
	{
		if (i == 1)
		{
			pid_lstnew(mini->commands->process->pid); // is this correct
			mini->commands->process->pid = fork();
		}
		if (process == -1)
			return (1); // check
		if (process == 0)
			which_child(mini, i, pos); // WE WERE HERE
		i++;
		pos++;
	}
	close_pipe(pipex.fd, pipex.argc);
	free_fd(pipex.fd, pipex.argc);
	close(pipex.in_file);
	close(pipex.out_f);
	waitpid(process, &pipex.status, 0);
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
	return (0);
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

int	start(t_data *mini_data)
{
	input_re(mini_data); // error checking ++ if no in file then ..??
	output_re(mini_data); // error checking ++ if no out file then ..??
	
	mini->commands->nb_cmds = lst_size(mini->commands);
	mini->commands->fd = open_pipes(mini);
	if (mini->commands->fd == NULL)
		exit(EXIT_FAILURE); // check if correct exit
	if (execute_pipe(mini) == 1) 
		exit(EXIT_FAILURE); // check if correct exit
	
    // if cmd == 1 ; do something seperate
    
	// other version needed without in and out files OR could we make a rule depending on < << >> > ??


	// don't forget to close files
	// and delete temp_file if it was there created by heredoc
	
	// pid's need to be freed
}


/*
	i left off at:
		-- start.c
			execute_pipe line 22 ++ 27: what to do with pids? how to create the list?
		-- child.c
			which_child: check line 46 ++ child_last ft
			which_child: check line 49 ++ child_middle ft
		-- utils.c
			check on the t_pid ones, if correct and needed??

	
	all error handling to go through
			
*/