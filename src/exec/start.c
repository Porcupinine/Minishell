/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/26 10:28:15 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>

static int	execute_pipe(t_data *mini)
{
	pid_t	temp;
	int		i;
	int 	pos;

	i = 1;
	pos = 0;
	while (i <= mini->commands->nb_cmds)
	{
		mini->process->pid = pid_lstadd_back(mini->process->pid, fork());
		temp = pid_lstlast(mini->process->pid);
		if (temp == -1)
			return (1); // check
		if (temp == 0)
			which_child(mini, i, pos);
		i++;
		pos++;
	}
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	free_fd(mini->commands->fd, mini->commands->nb_cmds);
	close(mini->commands->in);
	close(mini->commands->out);
	if (mini->commands->infiles->file->type == heredoc)
		unlink("tmp_file");
	waitpid(mini->process->pid, &mini->commands->status, 0); // does this work with: mini->process->pid ??
	if (WIFEXITED(mini->commands->status)) // check
		exit(WEXITSTATUS(mini->commands->status)); // check
	// something needs to be freed?? process for instance??
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
	input_re(mini); // error checking
	output_re(mini); // error checking 
	mini->commands->nb_cmds = lst_size(mini->commands);
	if (mini->commands->nb_cmds == 0)
	{
		close(mini->commands->in);
		close(mini->commands->out);
		if (mini->commands->infiles->file->type == heredoc)
			unlink("tmp_file");
	}
	else if (mini->commands->nb_cmds == 1) // I WAS HERE TRYING TO FIGURE OUT HOW TO APPROACH IF ONLY 1CMD
	{
		split_args(mini->commands->cmd, mini->mini_envp, mini); // just reuse this one right??
		close(mini->commands->in);
		close(mini->commands->out);
		if (mini->commands->infiles->file->type == heredoc)
			unlink("tmp_file");
	}
	else
	{
		mini->commands->fd = open_pipes(mini);
		if (mini->commands->fd == NULL)
			exit(EXIT_FAILURE); // check if correct exit
		if (execute_pipe(mini) == 1)
			exit(EXIT_FAILURE); // check if correct exit
		// pid's need to be freed??
	}
	return (0);  // right?? because if anything it will have errored in the input/output ft
}


/*
	i left off at:
		-- input_op.c --> CHECK ON THIS THING HERE
			i' not using find_arg ft, how come
		-- builtins.c --> WORKING ON THIS HERE
			go through them to adapt now we know the structure
		-- error.c
			write something for all the errors
		-- ...
			all error handling to go through
		-- start.c 
			HEREDOC CHECK: --> THINK THAT'S SOLVED NOW, check
				(limiter = hey)
					hallo\
					hey
					hey (only exists here and it gives back hallohey so rm the \) --> THINK THAT'S SOLVED NOW
				(limiter = he"y")
					it will disregard the quotes and just use hey as limiter --> THINK THAT'S SOLVED NOW

	QUESTION:
		-- what would be the best approach for the pids?? storing them in a struct or not?? PROBABLY 
		-- (LAURA) in echo should i still filter though the str see if there is a $ in there?? YES 
	
	
			
*/