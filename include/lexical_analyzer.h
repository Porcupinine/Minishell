/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analyzer.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:34:36 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 12:04:14 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYZER_H
# define LEXICAL_ANALYZER_H

# include "minishell.h"

/*defines to help set values for functions that search for quotes and metachars*/
# define QUOTES "\"'"
# define METACHAR " |><	"

/**
 * enums that symbolize the machine status
 * S_WAITTING is set if the states are metachars
 * S_WORD is set everytime a char is found
 * S_SQUOTES is set once the first single quote is found
 * S_DQUOTES is set once the first double quote is found
 */
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

/**
 * state machine that will that the command_line contained inside
 * the data struct and break it into tokens
 * @param mini_data data struct
 */
void	parse_machine(t_data *mini_data);
/**
 * operates on S_WHITESPACE state
 * @param parser
 */
void	token_space_newline(t_state_machine *parser);
/**
 * operates on S_PIPE state
 * @param parser
 */
void	token_pipe(t_state_machine *parser);
/**
 * operates S_BIG state
 * @param parser
 */
void	token_bigger(t_state_machine *parser);
/**
 * operates on S_SMALL state
 * @param parser
 */
void	token_smaller(t_state_machine *parser);
/**
 * operates on S_BIGBIG state
 * @param parser
 */
void	token_bigbig(t_state_machine *parser);
/**
 * operates on S_CHAR state
 * @param parser
 */
void	token_str(t_state_machine *parser);
/**
 * function is called once a char is found, if
 * that is the first found char, status is set from
 * S_WAITING to S_WORD, start is set and len starts to be
 * incremented
 * @param parser
 */
void	found_char(t_state_machine *parser);
/**
 * operates on S_SMALLSMALL state
 * @param parser
 */
void	token_smallsmall(t_state_machine *parser);
/**
 *
 * @param parser
 */
void	token_error(t_state_machine *parser);
/**
 * function called once double or single quotes are found
 * checks the status of the machine and set it either to a
 * S_DQUOTE, S_SQUOTE or S_WORD
 * @param parser
 */
void	found_quotes(t_state_machine *parser);
/**
 * parse the data from token list to a command list
 * @param parser for the token list
 * @param mini_data for command list
 */
void	parse(t_state_machine *parser, t_data *mini_data);
void	syntax_error(t_tokens **tokens, char c);
#endif //MINISHELL_LEXICAL_ANALYZER_H
