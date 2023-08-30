/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/29 16:44:03 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../Lib42/include/get_next_line.h"

void input_re(t_commands *commands)
{
    if (commands->infiles == NULL)
		commands->in = STDIN_FILENO;
	while (commands->infiles)
	{
		commands->in = open(commands->infiles->file, O_RDONLY, 0644);
		if (commands->in < 0)
		{
			builtin_err(commands->infiles->file, "No such file or directory"); // return?
			break ; // right??
		}
		if (commands->infiles->next != NULL)
			close(commands->in);
		commands->infiles = commands->infiles->next;
	}
}
