#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../Lib42/include/libft.h"

void handler(int num)
{

}

int main(int argc, char **argv, char **envp) {
    char *commands;

    if (argc != 1)
        ft_error("EROOR!!\nWrong amount of args!\n");
    signal(SIGINT, handler);
    while (1)
    {
        commands = readline("minishell: ");
        printf("%s", commands);
    }
}

//ctrl c kill runing child processe, make a handler that recognize if its parent or kid
//ctrl d kill them  all
// ctrl \ faz nada