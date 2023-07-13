//
// Created by Laura Praca Lacerda on 6/21/23.
//

#ifndef MINISHELL_TOLKEN_LIST_ACTIONS_H
#define MINISHELL_TOLKEN_LIST_ACTIONS_H

#include "minishell.h"
#include "lexical_analyzer.h"

void add_token(t_tokens **tokens, char *token, t_type type);
void print_tokens(t_tokens *tokens);
void add_token_point(t_token_point **token, t_state_machine *parser, t_type type);

#endif //MINISHELL_TOLKEN_LIST_ACTIONS_H
