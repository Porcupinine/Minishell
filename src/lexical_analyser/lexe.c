#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"

void break_cmd(t_data *mini_data)
{
    int end;
    int start;
    char *str;

    start = 0;
    end = 0;
    while (mini_data->command_line[end] != '\0')
    {
        if(mini_data->command_line[end] == ' ')
        {
            str = ft_substr(mini_data->command_line, start, end-start);
            add_tolken(&mini_data->tolkens_list, str);
            start = end+1;
        }
        end++;
    }
    print_tolkens(mini_data->tolkens_list);
}