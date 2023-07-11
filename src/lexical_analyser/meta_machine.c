#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_pipe(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|' || c == '<' || c == '>')
    {
        add_token(tokens_list, "|", false, T_PIPE);
        if (c == '|')
            parser->state = S_PIPE;
        if (c == '<')
            parser->state = S_SMALL;
        if (c == '>')
            parser->state = S_BIG;//TODO redirect pipedoesnt work
    }
    else
        add_token(tokens_list, "|",true, T_PIPE);
    if (ft_strchr(" |<>\"'", c) == 0)
        parser->state = S_CHAR;
    if (c == ' ' || c == '\n')
        parser->state = S_WHITESPACE;
}

void token_bigger(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|')
    {
        add_token(tokens_list, ">", false, T_BIG);
        parser->state = S_PIPE;
    }
    else if (c == '>')
    {
        add_token(tokens_list, ">>", true, T_BIGBIG);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, ">", true, T_BIG);
        if (c == '<')
            parser->state = S_SMALL;;
        if (ft_strchr(" |<>\"'", c) == 0)
            parser->state = S_CHAR;
        if (c == ' ' || c == '\n')
            parser->state = S_WHITESPACE;
    }
}

void token_smaller(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|')
    {
        add_token(tokens_list, "<", false, T_SMALL);
        parser->state = S_PIPE;
    }
    else if (c == '<')
    {
        add_token(tokens_list, "<<", true, T_SMALLSMALL);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, "<", true, T_SMALL);
        if (c == '>')
            parser->state = S_SMALL;;
        if (ft_strchr(" |<>\"'", c) == 0)
            parser->state = S_CHAR;
        if (c == ' ' ||  c == '\n')
            parser->state = S_WHITESPACE;
    }
}

void token_bigbig(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == )
    add_token(tokens_list, ">", true, T_BIG);
    if (ft_strchr(" |<>\"'", c) == 0)
        parser->state = S_CHAR;
}
