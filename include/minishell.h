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
typedef struct t_env_args
{
    char *name;
    char *content;
    struct t_env_args *next;
}s_env_args;

/**
 * list with all tolkens
 * @str
 * @in_file boolean in case need read from a file
 * @out_file boolean in case need to write on a file
 * @next next item on the list
 */
typedef struct t_tolkens
{
    char *str;
    bool in_file;
    bool out_file;
    bool s_quote;
    bool d_quote;
    struct t_tolkens *next;
}s_tolkens;

/**
 * Main struct with all the information that is needed to run
 * the commands given to minishell
 * @amount_of_tolkens how many item on the tolken list and 2D
 * array
 * @tolkens tolkens XD
 * @env_arg list of environment variables
 * @command_line original command line
 */
typedef struct t_data
{
    int amount_of_tolkens;
    int amount_of_env_args;
    char **tolkens;
    s_tolkens tolkens_list;
    s_env_args env_args;
    char *command_line;

}s_data;



#endif //MINISHELL_MINISHELL_H
