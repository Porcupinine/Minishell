//
// Created by Laura Praca Lacerda on 8/7/23.
//

#ifndef MINISHELL_ENVP_PARSER_H
#define MINISHELL_ENVP_PARSER_H

#include "minishell.h"

void parse_array_envp(t_data *mini_data, char **envp);
void parse_list_envp(t_data *mini_data, char **envp);

#endif //MINISHELL_ENVP_PARSER_H
