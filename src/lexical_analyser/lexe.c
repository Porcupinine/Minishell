#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_str(t_tokens **tokens_list, t_state_machine *parser, char c)
{
    if (ft_strchr(" |<>\"'", c) == 0)
         parser->token = append_char(parser->token, c);
    else
    {
        add_token(tokens_list, parser->token, true, T_CHAR);
        ft_bzero(parser->token, ft_strlen(parser->token));
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

void token_start(t_state_machine *parser, char c)
{
    if (ft_strchr(" |<>\"'", c) == 0)
        parser->state = S_CHAR;
    if(c == ' ')
        parser->state = S_WHITESPACE;
    //TODO other options even if they are error ???

}

void parse_machine(t_data *mini_data)
{
    t_state_machine *parser;

    parser = ft_calloc(1, sizeof (t_state_machine));
    if (parser == NULL)
        return ; //TODO fail?
    parser->token = "\0";
    parser->count = 0;
    token_start(parser, mini_data->command_line[parser->count]);
    while (mini_data->command_line[parser->count] != '\0')
    {
        if (parser->state == S_WHITESPACE)
            token_space_newline(parser, mini_data->command_line[parser->count]);
        else if (parser->state == S_CHAR)
            token_str(&mini_data->tokens_list, parser, mini_data->command_line[parser->count]);
        else if (parser->state == S_PIPE)
            token_pipe(&mini_data->tokens_list, parser, mini_data->command_line[parser->count]);
        else if (parser->state == S_SMALL)
            ;
        else if (parser->state == S_SMALSMAL)
            ;
        else if (parser->state == S_BIGBIG)
            ;
        else if (parser->state == S_BIG)
            ;
        else if (parser->state == S_DOBLEQUOTE)
            token_doublequotes(&mini_data->tokens_list, parser, mini_data->command_line);
        else if (parser->state == S_SINGLEQUOTE)
            ;
        else if (parser->state == S_ENVARG)
            ;
        parser->count++;
    }
    add_token(&mini_data->tokens_list, parser->token, true, T_CHAR);
}