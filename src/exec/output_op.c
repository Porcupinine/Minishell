/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/20 13:14:28 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
    for the output operators sorting out
        STEP 1:
            count the amount (as could be that we have multiple to create/output)
            
        use case for >
            redirects output to specified file, if not existing create it
        use case for >>
            
        use case with nothin ?


*/
#include "minishell.h"

#include <fcntl.h>

void output_re(t_data *mini)
{
    if (mini->commands->outfiles->file == NULL) // meaning no outfile
        // output will be on stdout
        // return something to notify about it
    while (1)
    {
        if (mini->commands->outfiles->file->next != NULL)
        {
            // if next != NULL then don't put the output there
           	mini->commands->out = open(mini->commands->outfiles->file, (int)(mini->commands->outfiles->file->type), 0644); // type needs to be int
			if (mini->commands->out < 0)
				// through an error -- no perm error
            close(mini->commands->out); // so we can leave the last one open in the end
		}	
        else
        {
            mini->commands->out = open(mini->commands->outfiles->file, (int)(mini->commands->outfiles->file->type), 0644); // type needs to be int
			if (mini->commands->out < 0)
				// through an error -- no perm error
			break ;
		}
        mini->commands->outfiles->file = mini->commands->outfiles->file->next;
    }
}
