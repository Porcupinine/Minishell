#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../Lib42/include/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"

void sigint_handler(int sig)
{
    write(1, "sigint\n", 7);
}

void sigquit_handler(int sig)
{
    write(1,"sigquit\n", 8);
}

int main(int argc, char **argv, char **envp)
{
    struct sigaction sigint_sa;
    struct sigaction sigquit_sa;
    t_data *mini_data;

    mini_data = malloc(1*sizeof(t_data));
    if (mini_data == NULL)
        ft_error("Data malloc fail!\n");
    mini_data->mini_envp = envp;
    sigquit_sa.sa_handler = &sigquit_handler;
    sigint_sa.sa_handler = &sigint_handler;
    if (argc != 1)
        ft_error("EROOR!!\nWrong amount of args!\n");
    sigaction(SIGQUIT, &sigquit_sa, NULL);
    sigaction(SIGINT, &sigint_sa, NULL);
    while (1)
    {
        mini_data->command_line = readline("\nminishell: ");
        printf("%s\n", mini_data->command_line);
        count_args(mini_data);
    }
}
