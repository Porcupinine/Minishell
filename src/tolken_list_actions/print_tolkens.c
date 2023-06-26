#include "../../include/minishell.h"
#include <stdio.h>

void print_tokens(t_tokens *tokens)
{
    while (tokens != NULL)
    {
        printf("%s\n", tokens->str);
        tokens = tokens->next;
    }
}