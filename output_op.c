/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/19 18:31:25 by dmaessen         ###   ########.fr       */
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
           	open(mini->commands->outfiles->file, (int)(mini->commands->outfiles->file->type), 0644); // type needs to be int
			// should also check for errors here tho..
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
