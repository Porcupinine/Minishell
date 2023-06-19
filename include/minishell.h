//
// Created by laura on 11-6-23.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <stdbool.h>

typedef struct t_env_args
{
    char *name;
    char *content;

}s_env_args;

typedef struct t_tolkens
{
    char *str;
    bool in_file;
    bool out_file;
}s_tolkens;

/**
 * @amount_of_args
 * @tolkens
 * @env_arg
 * @command_line
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
