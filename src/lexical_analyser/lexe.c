#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_str(t_tokens **tokens_list, t_state_machine *parser, char c,  char **buffer)
{
    if(ft_isalnum((int) c) != 0)
        *buffer = append_char(*buffer, c);
    else
    {
        add_token(tokens_list, *buffer, true, T_CHAR);
        ft_bzero(*buffer, ft_strlen(*buffer));
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
    char *buffer;
    int count;
    t_state_machine *parser;

    count = 0;
    buffer = ft_calloc(1, sizeof (char*));
    if (buffer == NULL)
        return ; //TODO fail?
    parser = ft_calloc(1, sizeof (t_state_machine));
    if (parser == NULL)
        return ; //TODO fail?
    token_start(parser, mini_data->command_line[count]);
    while (mini_data->command_line[count] != '\0')
    {
        if (parser->state == S_WHITESPACE)
            token_space_newline(parser, mini_data->command_line[count]);
        else if (parser->state == S_CHAR)
            token_str(&mini_data->tokens_list, parser, mini_data->command_line[count], &buffer);
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