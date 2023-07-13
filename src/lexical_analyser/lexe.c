#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_start(t_state_machine *parser, char c)
{

    if (ft_strchr(" |<>\"'", c) == 0)
	{
		parser->state = S_CHAR;
		parser->status = S_WORD;
	}
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
    parser->count = 0;
	parser->cmd = mini_data->command_line;
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
        parser->count++;
    }
    add_token(&mini_data->tokens_list, ft_substr(parser->cmd, parser->start, parser->len), T_CHAR);
}