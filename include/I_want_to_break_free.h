//
// Created by Laura Praca Lacerda on 7/31/23.
//

#ifndef I_WANT_TO_BREAK_FREE_H
# define I_WANT_TO_BREAK_FREE_H

#include "minishell.h"
#include "lexical_analyzer.h"

void free_token_list(t_tokens **tokens);
void free_cmd_list (t_commands **cmd);
void free_pid_list(t_pid **lst);

#endif //I_WANT_TO_BREAK_FREE_H
