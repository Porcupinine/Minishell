//
// Created by Laura Praca Lacerda on 8/21/23.
//

#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	set_signals(void);
void	return_prompt(void);

#endif //MINISHELL_UTILS_H
