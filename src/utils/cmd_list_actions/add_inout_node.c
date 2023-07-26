#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

static t_outfile *find_last(t_outfile *out)
{
	if (out == NULL)
		return(NULL);
	while (out->next != NULL)
		out = out->next;
	return (out);
}

void add_outfile(t_outfile **outfile, enum s_type type, char *str)
{
	t_outfile *new_out;
	t_outfile *last;

	last = NULL;
	new_out = ft_calloc(1, sizeof (t_outfile));
	if (new_out == NULL)
		;//TODO malloc fail
	if (type == T_BIG)
		new_out->type = REDIRECT_OUTPUT;
	if (type == T_BIGBIG)
		new_out->type = APPEND_OUTPUT;
	new_out->file = str;
	new_out->next = NULL;
	if (outfile == NULL)
		*outfile = new_out;
	else
	{
		last = find_last(*outfile);;
		last->next = new_out;
	}
}

void add_infile(t_infile **infile, enum s_type type, char *str)
{
	t_infile *new_in;
	t_infile *last;

	last = NULL;
	new_in = ft_calloc(1, sizeof (t_infile));
	if (new_in == NULL)
		;//TODO malloc fail
	if (type == T_SMALL)
		new_in>type = REDIRECT_INPUT;
	if (type == T_SMALLSMALL)
		new_in->type = HEREDOC;
	new_in->file = str;
	new_in->next = NULL;
}

void add_inout(t_commands **cmd, char *str, enum s_type type)
{
	if(type == T_BIG || type == T_BIGBIG)
		add_outfile;
	else
		add_infile;
	if (type == T_BIG)
		(*cmd)->outfiles->type = REDIRECT_OUTPUT;
	if (type == T_BIGBIG)
		(*cmd)->outfiles->type = APPEND_OUTPUT;
	if (type == T_SMALL)
		(*cmd)->infiles->type = REDIRECT_INPUT;
	if (type == T_SMALLSMALL)
		(*cmd)->infiles->type = HEREDOC;
}

void add_cmd_node(t_commands **cmd, t_commands *new_cmd)
{

}