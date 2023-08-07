//
// Created by Laura Praca Lacerda on 8/7/23.
//

#ifndef MINISHELL_ERRORS_H
#define MINISHELL_ERRORS_H

#include "minishell.h"
#include "lexical_analyzer.h"

void	syntax_error_parse(t_state_machine *parser, t_data *mini_data);
#endif //MINISHELL_ERRORS_H
