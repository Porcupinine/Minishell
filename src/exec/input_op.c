/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/02 14:26:47 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"

void	input_re(t_commands *commands, t_data *mini)
{
	if (commands->infiles == NULL)
		commands->in = STDIN_FILENO;
	while (commands->infiles)
	{
		commands->in = open(commands->infiles->file, O_RDONLY, 0644);
		if (commands->in < 0)
		{
			no_filedirectory(commands->infiles->file, mini);
			break ;
		}
		else
			set_exit_code(mini, 0);
		printf("IN INPUT_RE %d FILE NAME %s\n", commands->in, commands->infiles->file);
		if (commands->infiles->next != NULL)
			close(commands->in);
		commands->infiles = commands->infiles->next;
	}
}
