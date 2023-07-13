#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_str(t_tokens **tokens_list, t_state_machine *parser, char c)
{

	if (ft_strchr(" |<>\"'", c) == 0)
		parser->len++;
	else
	{
		add_token(tokens_list, ft_substr(parser->cmd, parser->start, parser->len),  T_CHAR);
		parser->len = 0;
		parser->status = S_WAITING;
		if(c == ' ' || c == '\n')
			parser->state = S_WHITESPACE;
		else if(c == '>')
			parser->state = S_BIG;
		else if(c == '<')
			parser->state = S_SMALL;
		else if(c == '|')
			parser->state = S_PIPE;
	}
}

void found_char(t_state_machine *parser)
{
	if (parser->status != S_WORD)
	{
		parser->status = S_WORD;
		parser->start = parser->count;
	}
	else
		parser->len++;
	parser->state = S_CHAR;
}