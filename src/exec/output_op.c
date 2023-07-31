/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 17:03:38 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void output_re(t_data *mini)
{
    if (mini->commands->outfiles->file == NULL)
	{
		mini->commands->out = STDOUT_FILENO;
		return (0); // or what??
	}
	else
	{
		while (1)
		{
			if (mini->commands->outfiles->next != NULL)
			{
				mini->commands->out = open(mini->commands->outfiles->file, (int)(mini->commands->outfiles->file->type), 0644); // type needs to be int
				if (mini->commands->out < 0)
 					// throw an error -- no perm error
				close(mini->commands->out); // so we can leave the last one open in the end
			}	
			else
			{
				mini->commands->out = open(mini->commands->outfiles->file, (int)(mini->commands->outfiles->file->type), 0644); // type needs to be int
				if (mini->commands->out < 0)
					// throw an error -- no perm error
				break ;
			}
			mini->commands->outfiles = mini->commands->outfiles->next;
		}
	}
}
