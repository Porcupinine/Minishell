#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../Lib42/include/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"

//void handler(int num)
//{
//    // writes signal used on the log?
//    if (//SIGINT, kill all kids (CTRL C))
//    else if (//SIGQUIT, do nothing (CTRL \))
//    else if (//EOF, kill family (CTRL D))
//}

int main(int argc, char **argv, char **envp)
{
//    struct sigaction sa;
    s_data *mini_data;

    mini_data = malloc(1*sizeof(s_data));
    if (mini_data == NULL)
        ft_error("Data malloc fail!\n");
//    sa.sa_handler = &handler;
//    if (argc != 1)
//        ft_error("EROOR!!\nWrong amount of args!\n");
//    signal(SIGINT, handler);
    while (1)
    {
        mini_data->command_line = readline("\nminishell: ");
        printf("%s\n", mini_data->command_line);
        count_args(mini_data);
    }
}
