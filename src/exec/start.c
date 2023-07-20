/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/20 14:05:29 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**open_pipes(t_data *mini)
{
	int		**fd;
	int		nb;
	int		i;

	nb = argc - 4;
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

int	start(t_data *mini_data)
{
	input_re(mini_data); // error checking ++ if no in file then ..??
	output_re(mini_data); // error checking ++ if no out file then ..??
	

	
	// still old stuff to check out if needed in the structure
		pipex.index = 0;
		pipex.fd = open_pipes(argc);
		if (pipex.fd == NULL)
			exit(EXIT_FAILURE);
		if (execute_pipe(pipex) == 1)
			exit(EXIT_FAILURE);
	}
    // if cmd == 1 ; do something seperate
    
	// other version needed without in and out files OR could we make a rule depending on < << >> > ??


	// don't forget to close files
	// and delete temp_file if it was there created by heredoc
}