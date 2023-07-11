#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_str(t_tokens **tokens_list, t_state_machine *parser, char c,  char *token)
{
    if(ft_isalnum((int) c) != 0)
        token = append_char(token, c);
    else
    {
        add_token(tokens_list, token, true, T_CHAR);
        ft_bzero(token, ft_strlen(token));
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
    if(ft_isalnum((int) c) != 0)
        parser->state = S_CHAR;
    if(c == ' ')
        parser->state = S_WHITESPACE;
}
void parse_machine(t_data *mini_data)
{
    int count;
    t_state_machine *parser;

    count = 0;
    parser = ft_calloc(1, sizeof (t_state_machine));
    if (parser == NULL)
        return ; //TODO fail?
    token_start(parser, mini_data->command_line[count]);
    while (mini_data->command_line[count] != '\0')
    {
        if (parser->state == S_WHITESPACE)
            token_space_newline(parser, mini_data->command_line[count]);
        else if (parser->state == S_CHAR)
            token_str(&mini_data->tokens_list, parser, mini_data->command_line[count], parser->token);
        else if (parser->state == S_PIPE)
            token_pipe(&mini_data->tokens_list, parser, mini_data->command_line[count]);
        else if (parser->state == S_SMALL)
            ;
        else if (parser->state == S_SMALSMAL)
            ;
        else if (parser->state == S_BIGBIG)
            ;
        else if (parser->state == S_BIG)
            ;
        else if (parser->state == S_DOBLEQUOTE)
            ;
        else if (parser->state == S_SINGLEQUOTE)
            ;
        else if (parser->state == S_ENVARG)
            ;
        count++;
    }
}