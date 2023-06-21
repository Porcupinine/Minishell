#include "../../include/minishell.h"
#include <stdlib.h>

void check_for_args(t_data *mini_data)
{
    int count_for;
    int count_back;
    int count_arg;
    char *arg;
    char *content;

    count_for = 0;
    count_back = 0;
    count_arg = 0;
    while (mini_data->command_line[count_for] != '\0')
    {
        if (mini_data->command_line[count_for] == '=')
        {
            count_back = count_for;
            while (mini_data->command_line[count_for] != ' ')
                count_back--;
            arg = malloc(count_for - count_back);
            while (count_back != count_for)
            {
                arg[count_arg] = mini_data->command_line[count_back];
                count_back++;
            }
        }
    }
}
