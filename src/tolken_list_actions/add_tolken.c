//
// Created by Laura Praca Lacerda on 6/21/23.
//

#include <stdlib.h>
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

static t_tokens *find_last(t_tokens *token)
{
    t_tokens *temp;

    temp = token;
    if (temp == NULL)
        return (NULL);
//    printf("%p\n", token);
    while (temp->next != NULL)
    {
        temp = temp->next;
//        printf("%p\n", temp);
    }
    return (temp);
}

void add_token(t_tokens **tokens, char *token, bool status, t_type type)
{
    t_tokens *new_token;

    new_token = malloc(sizeof(t_tokens));
    if(new_token == NULL)
        ft_error("Malloc token fail\n");
    new_token->str = token;
    new_token->status = status;
    new_token->type = type;
    new_token->next = NULL;
    if(*tokens == NULL)
        *tokens = new_token;
    else
    {
        t_tokens *last_node;

        last_node = find_last(*tokens);
        last_node->next = new_token;
    }
}


