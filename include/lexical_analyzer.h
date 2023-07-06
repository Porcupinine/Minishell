//
// Created by Laura Praca Lacerda on 6/21/23.
//

#ifndef MINISHELL_LEXICAL_ANALYZER_H
#define MINISHELL_LEXICAL_ANALYZER_H

#include "minishell.h"

typedef enum SM_STATES
{
    S_WHITESPACE = ' ',
    S_METACHAR,
    S_CHAR,
    S_END,
}SM_STATES;

typedef struct s_state_machine
{
    SM_STATES state;
    char *tolken;
    SM_STATES next_state;
}t_state_machine;


void break_cmd(t_data *mini_data);

#endif //MINISHELL_LEXICAL_ANALYZER_H
