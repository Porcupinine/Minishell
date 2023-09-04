/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inout_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:51:29 by laura             #+#    #+#             */
/*   Updated: 2023/09/01 17:22:14 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/utils.h"
#include "../../../include/exec.h"

static t_outfile	*find_last_out(t_outfile *out)
{
	t_outfile	*tmp;

	tmp = out;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

static t_infile	*find_last_in(t_infile *in)
{
	t_infile	*tmp;

	tmp = in;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

static void	add_outfile(t_outfile **outfile, enum s_type type, char *str)
{
	t_outfile	*new_out;
	t_outfile	*last;

	last = NULL;
	new_out = ft_calloc_exit(1, sizeof (t_outfile));
	if (type == T_BIG)
		new_out->type = REDIRECT_OUTPUT;
	if (type == T_BIGBIG)
		new_out->type = APPEND_OUTPUT;
	new_out->file = ft_strdup(str);
	new_out->next = NULL;
	if (*outfile == NULL)
		*outfile = new_out;
	else
	{
		last = find_last_out(*outfile);
		last->next = new_out;
	}
}

static void	add_infile(t_infile **infile, enum s_type type, char *str)
{
	t_infile	*new_in;
	t_infile	*last;

	last = NULL;
	new_in = ft_calloc_exit(1, sizeof (t_infile));
	if (type == T_SMALL)
		new_in->type = REDIRECT_INPUT;
	if (type == T_SMALLSMALL)
		new_in->type = HEREDOC;
	new_in->file = ft_strdup(str);
	new_in->next = NULL;
	if (*infile == NULL)
		*infile = new_in;
	else
	{
		last = find_last_in(*infile);
		last->next = new_in;
	}
}

void	add_inout(t_commands **cmd, char *str, enum s_type type, \
			t_data *mini_data)
{
	char	*tmp;

	tmp = expanded(str, mini_data);
	if (type == T_BIG || type == T_BIGBIG)
		add_outfile(&(*cmd)->outfiles, type, tmp);
	else
		add_infile(&(*cmd)->infiles, type, tmp);
}
