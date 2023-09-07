/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/04 13:38:01 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"

void	input_re(t_commands *commands, t_data *mini)
{
	t_infile *temp;

	temp = commands->infiles;
	if (temp == NULL)
		commands->in = STDIN_FILENO;
	while (temp)
	{
		commands->in = open(temp->file, O_RDONLY, 0644);
		if (commands->in < 0)
		{
			no_filedirectory(temp->file, mini);
			break ;
		}
		else
			set_exit_code(mini, 0);
		if (temp->next != NULL)
			close(commands->in);
		temp = temp->next;
	}
}
