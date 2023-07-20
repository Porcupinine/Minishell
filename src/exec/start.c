/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/20 11:38:25 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start(t_data *mini_data)
{
	input_re(mini_data);
		// if -1 ??
		// if its heredoc tho redirect to somewhere before to read from stdin
	output_re(mini_data);
		// if -1 ??
	
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