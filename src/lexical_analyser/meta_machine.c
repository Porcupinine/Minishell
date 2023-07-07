#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_pipe(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '\0') // huston we have a problem
    {
        add_token(tokens_list, "|", false, T_PIPE);
        if (c == '|')
            parser->state = S_PIPE;
        if (c == '<')
            parser->state = S_SMALL;
        if (c == '>')
            parser->state = S_BIG;
        if (c == '\0')
            parser->state = S_END;
//        parser->state = S_INVALID;
    }
    else
        add_token(tokens_list, "|",true, T_PIPE);
    if (ft_isalnum(c) != 0)
        parser->state = S_CHAR;
    if (c == ' ' || c == '\n')
        parser->state = S_WHITESPACE;
}

void token_bigger(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|' || c == '\0') // huston we have a problem
    {
        add_token(tokens_list, ">", false, T_PIPE);
        if (c == '|')
            parser->state = S_PIPE;
        if (c == '\0')
            parser->state = S_END;
//        parser->state = S_INVALID;
    }
    else if (c == '>')
    {
        add_token(tokens_list, ">>", true, T_PIPE);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, ">", true, T_PIPE);
        if (c == '<')
            parser->state = S_SMALL;;
        if (ft_isalnum(c) != 0)
            parser->state = S_CHAR;
        if (c == ' ' || c == '\n')
            parser->state = S_WHITESPACE;
    }
}

void token_smaller(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (c == '|' || c == '\0') // huston we have a problem
    {
        add_token(tokens_list, "<", false, T_PIPE);
        if (c == '|')
            parser->state = S_PIPE;
        if (c == '\0')
            parser->state = S_END;
//        parser->state = S_INVALID;
    }
    else if (c == '<')
    {
        add_token(tokens_list, "<<", true, T_PIPE);
        parser->state = S_BIGBIG;;
    }
    else
    {
        add_token(tokens_list, "<", true, T_PIPE);
        if (c == '>')
            parser->state = S_SMALL;;
        if (ft_isalnum(c) != 0)
            parser->state = S_CHAR;
        if (c == ' ' ||  c == '\n')
            parser->state = S_WHITESPACE;
    }
}