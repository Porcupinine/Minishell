#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>


void token_space_newline(t_state_machine *parser, char c)
{
	if (ft_strchr(" |<>\"'", c) == 0)
	{
		if (parser->status != S_WORD)
		{
			parser->status = S_WORD;
			parser->start = parser->count;
		}
		parser->len++;
		parser->state = S_CHAR;
	}
    else
    {
        if (c == '|')
            parser->state = S_PIPE;
        else if (c == '>')
            parser->state = S_BIG;
        else if (c == '<')
            parser->state = S_SMALL;
    }
}