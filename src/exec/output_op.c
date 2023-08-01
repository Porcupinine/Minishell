/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/01 20:33:14 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static void open_lastfile(t_data *mini, t_outfile *last_out)
{
	if (last_out->file->type == APPEND) // check id remember the term we agreed on
		mini->commands->out = open(last_out->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		mini->commands->out = open(last_out->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void output_re(t_data *mini)
{
    if (mini->commands->outfiles->file == NULL)
		mini->commands->out = STDOUT_FILENO;
	else
	{
		while (1)
		{
			if (mini->commands->outfiles->next != NULL)
			{
				if (mini->commands->outfiles->file->type == APPEND) // check id remember the term we agreed on
					mini->commands->out = open(mini->commands->outfiles->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
				else
					mini->commands->out = open(mini->commands->outfiles->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (mini->commands->out < 0)
 					builtin_err(mini->commands->outfiles->file, "No such file or directory"); // return?
				close(mini->commands->out); // so we can leave the last one open in the end
			}	
			else
			{
				open_lastfile(mini, mini->commands->outfiles); 
				if (mini->commands->out < 0)
 					builtin_err(mini->commands->outfiles->file, "No such file or directory"); // return?
				break ;
			}
			mini->commands->outfiles = mini->commands->outfiles->next;
		}
	}
}
