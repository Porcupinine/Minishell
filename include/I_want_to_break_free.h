//
// Created by Laura Praca Lacerda on 7/31/23.
//

#ifndef MINISHELL_I_WANT_TO_BREAK_FREE_H
#define MINISHELL_I_WANT_TO_BREAK_FREE_H

#include "minishell.h"
#include "lexical_analyzer.h"

void free_token_list(t_tokens **tokens);
void free_cmd_list (t_commands **cmd);

#endif //MINISHELL_I_WANT_TO_BREAK_FREE_H
