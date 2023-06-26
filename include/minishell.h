//
// Created by laura on 11-6-23.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <signal.h>
#include <stdbool.h>

/**
 * list of child PIDs
 */
typedef struct s_pid
{
    pid_t pid;
    struct s_pid *next;
}t_pid;

/**
 * list of environment variables
 * @name given name of the variable
 * @content content of the variable
 * @next next variable
 */
typedef struct s_env_args
{
    char *name;
    char *content;
    struct s_env_args *next;
}t_env_args;

/**
 * list with all tolkens
 * @str
 * @in_file boolean in case need read from a file
 * @out_file boolean in case need to write on a file
 * @s_quote if it's between single quotes
 * @d_quote if it's between double quotes
 * @next next item on the list
 */
typedef struct s_tokens
{
    char *str;
    struct s_tokens *next;
}t_tokens;

/**
 * Main struct with all the information that is needed to run
 * the commands given to minishell
 * @amount_of_tolkens how many item on the tolken list and 2D
 * array
 * @tolkens tolkens XD
 * @env_arg list of environment variables
 * @command_line original command line
 */
typedef struct s_data
{
    int amount_of_tokens;
    int amount_of_env_args;
    char **tokens;
    char **mini_envp;
    t_tokens *tokens_list;
    t_env_args *env_args;
    char *command_line;
    int count_s_quote;
    int count_d_quote;
}t_data;



#endif //MINISHELL_MINISHELL_H
