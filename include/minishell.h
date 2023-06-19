//
// Created by laura on 11-6-23.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

/**
 * @amount_of_args
 * @tolkens
 * @env_arg
 * @command_line
 */
typedef struct t_data
{
    int amount_of_tolkens;
    char **tolkens;
    char **env_arg;
    char *command_line;

}s_data;

#endif //MINISHELL_MINISHELL_H
