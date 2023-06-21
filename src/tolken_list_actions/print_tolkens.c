#include "../../include/minishell.h"
#include <stdio.h>

void print_tolkens(t_tolkens *tolkens)
{
    while (tolkens != NULL)
    {
        printf("%s\n", tolkens->str);
        tolkens = tolkens->next;
    }
}