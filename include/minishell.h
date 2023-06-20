//
// Created by laura on 11-6-23.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <stdbool.h>

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
typedef struct s_tolkens
{
    char *str;
    bool in_file;
    bool out_file;
    bool s_quote;
    bool d_quote;
    struct s_tolkens *next;
}t_tolkens;

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
    int amount_of_tolkens;
    int amount_of_env_args;
    char **tolkens;
    char **mini_envp;
    t_tolkens tolkens_list;
    t_env_args env_args;
    char *command_line;
    int count_s_quote;
    int count_d_quote;


}t_data;



#endif //MINISHELL_MINISHELL_H
