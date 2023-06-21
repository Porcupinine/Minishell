//
// Created by Laura Praca Lacerda on 6/20/23.
//
#include "../../include/minishell.h"
#include <stdlib.h>
#include "../../Lib42/include/libft.h"

void add_arg(t_env_args *args, char *name, char* value)
{
    t_env_args *new_arg;

    new_arg = malloc(sizeof(t_env_args));
    if (new_arg == NULL)
        ft_error("Malloc arg fail\n");
    args->next = new_arg;
    new_arg->name = name;
    new_arg->content = value;
    new_arg->next = NULL;
}