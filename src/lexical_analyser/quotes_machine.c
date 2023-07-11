#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void token_doublequotes(t_tokens **tokens_list, t_state_machine *parser, int *count, char *cmd_line)
{
    char *str;

    str = ft_calloc(1, sizeof(char *));
    if (str == NULL)
        return; //TODO should we quit??? save double quote
        
    while (cmd_line[*count] != '"')
    {
        if (cmd_line[*count] != '$')
        {
            add_token(tokens_list, str,true, T_CHAR);
            parser->state = S_ENVARG;
            return;
        }
        str = append_char(str, cmd_line[*count]);
        count++;
    }
    add_token(tokens_list, str, true, T_CHAR);

    //TODO where can we go from here
}

void token_singlequote(t_tokens **tokens_list, t_state_machine *parser, int *count, char *cmd_line)
{
    char *str;

    str = ft_calloc(1, sizeof(char *));
    if (str == NULL)
        return; //TODO should we quit???
    while (cmd_line[*count] != '\'')
    {
        str = append_char(str, cmd_line[*count]);
        count++;
    }
    add_token(tokens_list, str, true, T_CHAR);

    //TODO where can we go from here
}