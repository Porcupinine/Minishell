/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:21:59 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 17:26:59 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void	output_re(t_commands *commands, t_data *mini)
{
	t_outfile	*temp;

	temp = commands->outfiles;
	if (temp == NULL)
		commands->out = STDOUT_FILENO;
	while (temp)
	{
		if (temp->type == APPEND_OUTPUT)
			commands->out = open(temp->file, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			commands->out = open(temp->file, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (commands->out < 0)
			return (err_msg(temp->file, \
					"No such file or directory"));
		else
			set_exit_code(mini, 0);
		if (temp->next != NULL)
			close(commands->out);
		temp = temp->next;
	}
}
