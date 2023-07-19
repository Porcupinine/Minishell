/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/19 18:29:45 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
    for the input operators sorting out
        use case for <
            read from file that comes after 
            O_RDONLY
            F_OK ??
        use case for <<
            redirect input to stdin until LIMITER
            --> maybe something for Laura to deal with tho and pass me on the input
        use case with nothin ?

    QUESTION
        can we have multiple after one another??

*/

#include "minishell.h"

#include <fcntl.h>
#include <stdlib.h>

void input_re(t_data *mini)
{
    if (mini->commands->infiles->file == NULL) // meaning no intfile
        // return something to notify about it
    else if (mini->commands->infiles->file->type == heredoc)
		mini->commands->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		// if its heredoc tho redirect to somewhere before to read from stdin
    else
        mini->commands->in = open(mini->commands->infiles->file, O_RDONLY, 0644);
	if (mini->commands->in < 0)
		// through an error
}