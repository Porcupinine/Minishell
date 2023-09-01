/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/01 17:15:02 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

static void	open_lastfile(t_commands *commands, t_outfile *last_out)
{
	if (last_out->type == APPEND_OUTPUT)
		commands->out = open(last_out->file,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		commands->out = open(last_out->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

static void	open_close_file(t_commands *commands)
{
	if (commands->outfiles->type == APPEND_OUTPUT)
		commands->out = open(commands->outfiles->file,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		commands->out = open(commands->outfiles->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	output_re(t_commands *commands)
{
	if (commands->outfiles == NULL)
		commands->out = STDOUT_FILENO;
	else
	{
		while (1)
		{
			if (commands->outfiles->next != NULL)
			{
				open_close_file(commands);
				if (commands->out < 0)
					return (err_msg(commands->outfiles->file,
							"No such file or directory"));
				close(commands->out);
			}
			else
			{
				open_lastfile(commands, commands->outfiles); 
				if (commands->out < 0)
					return (err_msg(commands->outfiles->file,
							"No such file or directory"));
				break ;
			}
			commands->outfiles = commands->outfiles->next;
		}
	}
}
