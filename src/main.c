#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../Lib42/include/libft.h"

void handler(int num)
{
    // writes signal used on the log?
    if (//SIGINT, kill all kids (CTRL C))
    else if (//SIGQUIT, kill family (CTRL D))
    else if (// , do nothing (CTRL \))
}

int main(int argc, char **argv, char **envp)
{
    char *commands;
    struct sigaction sa;

    sa.sa_handler = &handler;
    if (argc != 1)
        ft_error("EROOR!!\nWrong amount of args!\n");
    signal(SIGINT, handler);
    sigaction()
    while (1)
    {
        commands = readline("minishell: ");
        printf("%s", commands);
    }
}

//ctrl c kill runing child processe, make a handler that recognize if its parent or kid
//ctrl d kill them  all
// ctrl \ faz nada