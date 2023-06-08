#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int num)
{

}
int main(int argc, char **argv, char **envp) {
    char *commands;

    signal(SIGINT, handler);
    while (1)
    {
        commands = readline("minishell: ");
        printf("%s", commands);
    }
}