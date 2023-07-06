#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"

void if_pipe(t_data *mini_data, int start, int end)
{
    if (mini_data->command_line[end+1] != ' ')
    {
        char *str;

        add_token(&mini_data->tokens_list, "|");
        end++;
        str = ft_substr(mini_data->command_line, start, end-start);
        add_token(&mini_data->tokens_list, str);
    }
}

void if_iqual(t_data *minidata, int start, int end)
{

}

void break_cmd(t_data *mini_data)
{
    int end;
    int start;
    char *str;

    start = 0;
    end = 0;
    while (mini_data->command_line[end] != '\0')
    {
        if(ft_strchr(" |=", mini_data->command_line[end]) != 0 )
        {
            str = ft_substr(mini_data->command_line, start, end-start);
            add_token(&mini_data->tokens_list, str);
            if (mini_data->command_line[end] == '|')
            {
                add_token(&mini_data->tokens_list, "|");
                end++;
            }
            if (mini_data->command_line[end] == '=')
            {
                add_token(&mini_data->tokens_list, "=");
                end++;
            }
            while(mini_data->command_line[end] == ' ')
                end++;
            start = end;
        }
        end++;
    }
    str = ft_substr(mini_data->command_line, start, end-start);
    add_token(&mini_data->tokens_list, str);
    print_tokens(mini_data->tokens_list);
}
void parse_str(t_state_machine *parser, char *command)
{
    char *buffer;

}

void parse_machine(t_state_machine *parser, char *command)
{
    while (*command != '\0')
    {
        if (parser->state == S_WHITESPACE)
        {
            if (*command == ' ') parser->state = S_WHITESPACE;
            if (ft_isalnum(*command) != 0) parser->state = S_CHAR;
            if (ft_strchr("<>|", *command) != 0) parser->state = S_METACHAR;
            if (*command == '\0') parser->state = S_END;

        }
        else if (parser->state == S_CHAR)
        {w
            if (*command ==)
        }
        else if (parser->state == S_END)
        {

        }
        else if (parser->state == S_METACHAR)
        {

        }
        command++;
    }
}