#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>

void token_pipe(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|' || c == '<' || c == '>')
    {
        printf("\033[1;31m Syntax error\n \033[1;31m");
        //TODO syntax error
    }
    else
        add_token(tokens_list, "|", T_PIPE);
    if (ft_strchr(" |<>\"'", c) == 0)
		found_char(parser);
    if (c == ' ' || c == '\n')
        parser->state = S_WHITESPACE;
}

void token_bigger(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|')
    {
        printf("\033[1;31m Syntax error\n \033[1;31m");
        //TODO syntax error
    }
    else if (c == '>')
    {
        add_token(tokens_list, ">>", T_BIGBIG);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, ">", T_BIG);
        if (c == '<')
            parser->state = S_SMALL;;
        if (ft_strchr(" |<>\"'", c) == 0)
			found_char(parser);
		if (c == ' ' || c == '\n')
            parser->state = S_WHITESPACE;
    }
}

void token_smaller(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|')
    {
        add_token(tokens_list, "<", T_SMALL);
        parser->state = S_PIPE;
    }
    else if (c == '<')
    {
        add_token(tokens_list, "<<", T_SMALLSMALL);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, "<", T_SMALL);
        if (c == '>')
            parser->state = S_SMALL;;
        if (ft_strchr(" |<>\"'", c) == 0)
			found_char(parser);
		if (c == ' ' ||  c == '\n')
            parser->state = S_WHITESPACE;
    }
}

void token_bigbig(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '>')
	{
		//TODO syntax error
	}
    add_token(tokens_list, ">", T_BIG);
    if (ft_strchr(" |<>\"'", c) == 0)
		found_char(parser);
}
