//
// Created by Laura Praca Lacerda on 6/21/23.
//

#ifndef MINISHELL_LEXICAL_ANALYZER_H
#define MINISHELL_LEXICAL_ANALYZER_H

#include "minishell.h"

typedef enum SM_STATUS
{
	S_WAITING,
	S_WORD,
	S_END,
}SM_STATUS;

typedef enum SM_STATES
{
    S_WHITESPACE,
    S_PIPE,
    S_BIG,
    S_BIGBIG,
    S_SMALL,
    S_SMALSMAL,
    S_CHAR,
    S_INVALID,
    S_DOBLEQUOTE,
    S_SINGLEQUOTE,
    S_ENVARG,
}SM_STATES;

/**
 *@param token_start pointer to the initil position of the
 * tolken in the command line
 * @param len size of the string to be tolkenized
 */
typedef struct s_state_machine
{
    SM_STATES state;
	SM_STATUS status;
    char *cmd;
    int count;
	int start;
	int len;
    SM_STATES prev_state;
}t_state_machine;

void parse_machine(t_data *mini_data);
void break_cmd(t_data *mini_data);
void change_state(t_state_machine *parser, char c);
void token_space_newline(t_state_machine *parser, char c);
void token_pipe(t_tokens **tokens_list, t_state_machine *parser, char c);
void token_bigger(t_tokens **tokens_list, t_state_machine *parser, char c);
void token_smaller(t_tokens **tokens_list, t_state_machine *parser, char c);
void token_doublequotes(t_tokens **tokens_list, t_state_machine *parser, char *cmd_line);
void token_bigbig(t_tokens **tokens_list, t_state_machine *parser, char c);
void token_str(t_tokens **tokens_list, t_state_machine *parser, char c);
void found_char(t_state_machine *parser);

#endif //MINISHELL_LEXICAL_ANALYZER_H
