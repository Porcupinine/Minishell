/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analyzer.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:34:36 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:36:23 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYZER_H
# define LEXICAL_ANALYZER_H

# include "minishell.h"

#define quotes "\"'"
#define metachar " |><	"

typedef enum s_SM_STATUS
{
	S_WAITING,
	S_WORD,
	S_DQUOTES,
	S_SQUOTES,
	S_END,
}t_SM_STATUS;

typedef enum s_SM_STATES
{
	S_WHITESPACE,
	S_PIPE,
	S_BIG,
	S_BIGBIG,
	S_SMALL,
	S_SMALSMAL,
	S_CHAR,
	S_ERROR,
}t_SM_STATES;

typedef enum s_type
{
	T_PIPE,
	T_BIG,
	T_BIGBIG,
	T_SMALL,
	T_SMALLSMALL,
	T_CHAR,
	T_END,
}t_type;

/**
 * @param str
 * @next
 * @param status true if valid, false if error was found
 * @param type type of token
 * @param str tolken
 * @param next pointer to next tolken
 */
typedef struct s_tokens
{
	t_type			type;
	char			*str;
	struct s_tokens	*next;
}t_tokens;

/**
 *@param token_start pointer to the initil position of the
 * tolken in the command line
 * @param len size of the string to be tolkenized
 */
typedef struct s_state_machine
{
	t_SM_STATES	state;
	t_SM_STATUS	status;
	t_tokens	*tokens_list;
	char		*cmd;
	int			count;
	int			start;
	int			len;
}t_state_machine;

void	parse_machine(t_data *mini_data);
void	token_space_newline(t_state_machine *parser);
void	token_pipe(t_state_machine *parser);
void	token_bigger(t_state_machine *parser);
void	token_smaller(t_state_machine *parser);
void	token_bigbig(t_state_machine *parser);
void	token_str(t_state_machine *parser);
void	found_char(t_state_machine *parser);
void	token_smallsmall(t_state_machine *parser);
void	token_error(t_state_machine *parser);
void	found_quotes(t_state_machine *parser);

#endif //MINISHELL_LEXICAL_ANALYZER_H
