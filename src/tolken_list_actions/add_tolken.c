//
// Created by Laura Praca Lacerda on 6/21/23.
//

#include <stdlib.h>
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>
#include "../../include/lexical_analyzer.h"

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

static t_token_point *find_last_point(t_token_point *token)
{
	t_token_point *temp;

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
void add_token(t_tokens **tokens, char *token, t_type type)
{
    t_tokens *new_token;

    new_token = malloc(sizeof(t_tokens));
    if(new_token == NULL)
        ft_error("Malloc token fail\n");
    new_token->str = token;
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

void add_token_point(t_token_point **token, int len, char *start, t_type type)
{
	t_token_point *new_token;

	new_token = ft_calloc(1, sizeof(t_token_point));
	if (new_token == NULL)
	{

	}//TODO Malloc error;
	new_token->len = len;
	new_token->start = start;
	new_token->type = type;
	new_token->next = NULL;
	if(*token == NULL)
		*token = new_token;
	else
	{
		t_token_point *last_node;

		last_node = find_last_point(*token);
		last_node->next = new_token;
	}
}

