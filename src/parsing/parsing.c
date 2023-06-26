#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

void count_args(t_data *mini_data)
{
    int walk;

    mini_data->count_d_quote = 0;
    mini_data->count_s_quote = 0;
    walk = 0;
    mini_data->amount_of_tolkens = 0;
    while (mini_data->command_line[walk] != '\0')
    {
        if(ft_strchr("\"\'<>|$", mini_data->command_line[walk]) != 0)
        {
            if((mini_data->command_line[walk] == '<' && mini_data->command_line[walk + 1] == '<') ||
                    (mini_data->command_line[walk] == '>' && mini_data->command_line[walk + 1] == '>'))
                walk++;
            if (mini_data->command_line[walk] == '\"')
                mini_data->count_d_quote++;
            if (mini_data->command_line[walk] == '\'')
                mini_data->count_s_quote++;
            mini_data->amount_of_tolkens++;
            printf("%s",&mini_data->command_line[walk]);
        }
        walk++;
    }
}


//take in account << and <
//take in account closed quotes
// to malloc 2D array, check amount of separators +1 ?
// separators can be " ' < > | also $ to find Arg
// if find any " or ' stop looking for other until finds the next one
// use string search to find first separator, register separator gets info till it and check for spaces.
//check if it's a command, store inside the 2d array, update amount of commands
// if no separator is found just check for spaces and if it's a valid input add to 2D array and increment number of args
//remaloc array? or can search for how many separators and malloc saparators + 1?




