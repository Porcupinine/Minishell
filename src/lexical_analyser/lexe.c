#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_str(t_tokens **tokens_list, t_state_machine *parser, char c,  char **buffer)
{
    if(ft_isalnum((int) c) != 0)
    {
        add_token(tokens_list, *buffer, true, T_CHAR);
        if(c == ' ' || c == '\n')
            parser->state = S_WHITESPACE;
        else if(c == '>')
            parser->state = S_BIG;
        else if(c == '<')
            parser->state = S_SMALL;
        else if(c == '|')
            parser->state = S_PIPE;
    }
    else
        ft_strlcat(*buffer, (const char *) c, 1);
}

void parse_machine(t_data *mini_data, t_state_machine *parser)
{
    char *buffer;
    int count;

    count = 0;
    buffer = ft_calloc(1, sizeof (char*));
    while (mini_data->command_line[count] != '\0')
    {
        if (parser->state == S_WHITESPACE)
        {
            token_space_newline(parser, mini_data->command_line[count]);
        }
        else if (parser->state == S_CHAR)
        {
            token_str(&mini_data->tokens_list, parser, mini_data->command_line[count], &buffer);
        }
        else if (parser->state == S_PIPE)
        {
            token_pipe(&mini_data->tokens_list, parser, mini_data->command_line[count]);
        }
        count++;
    }
}