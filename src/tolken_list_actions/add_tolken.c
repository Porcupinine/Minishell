//
// Created by Laura Praca Lacerda on 6/21/23.
//

#include <stdlib.h>
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"

void add_tolken(t_tolkens *tolkens, char *tolken)
{
    t_tolkens *new_tolken;

    new_tolken = malloc(sizeof(t_tolkens));
    if(new_tolken == NULL)
        ft_error("Malloc tolken fail\n");
    tolkens->next = new_tolken;
    new_tolken->str = tolken;
    new_tolken->next = NULL;
}

