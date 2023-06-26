//
// Created by Laura Praca Lacerda on 6/21/23.
//

#include <stdlib.h>
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"

static t_tolkens *find_last(t_tolkens *tolken)
{
    while (tolken->next != NULL)
        tolken = tolken->next;
    return (tolken);
}

void add_tolken(t_tolkens **tolkens, char *tolken)
{
    t_tolkens *new_tolken;

    new_tolken = malloc(sizeof(t_tolkens));
    if(new_tolken == NULL)
        ft_error("Malloc tolken fail\n");
    new_tolken->str = tolken;
    new_tolken->next = NULL;
    if(*tolkens == NULL)
        *tolkens = new_tolken;
    else
    {
        t_tolkens *last_node;

        last_node = find_last(*tolkens);
        last_node->next = new_tolken;
    }
}


