//
// Created by Laura Praca Lacerda on 6/21/23.
//

#ifndef MINISHELL_TOLKEN_LIST_ACTIONS_H
#define MINISHELL_TOLKEN_LIST_ACTIONS_H

#include "minishell.h"

void add_token(t_tokens **tokens, char *token, bool status, t_type type);
void print_tokens(t_tokens *tokens);

#endif //MINISHELL_TOLKEN_LIST_ACTIONS_H
