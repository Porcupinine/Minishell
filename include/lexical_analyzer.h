/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analyzer.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 16:15:36 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/09/04 14:22:11 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYZER_H
# define LEXICAL_ANALYZER_H

# include "minishell.h"

/*defines to help set values for functions that search for 
quotes and metachars*/
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

/**
 * enum that symbolize the current type of character
 * S_WHITESPACE set when a white space is found, they
 * are supposed to be ignored
 * S_PIPE pipes get theis own token and are ignored 
 * during the parsing 
 * S_BIG redirection output
 * S_BIGBIG append output
 * S_SMALL redirection input
 * S_SMALSMAL heredoc
 * S_CHAR any character that is not a "metachar"
 * S_ERROR Huoston we have a problem
*/
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

/**
 * types are set in the token list and used for parsing
 * T_PIPE pipes will be ignored 
 * T_BIG redirection output
 * T_BIGBIG append output
 * T_SMALL redirection input
 * T_SMALSMAL heredoc
 * T_CHAR token is suposed to be trated as regular string
*/
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
 * @param str token AKA valid char or char set
 * @param type type of token 
 * @param next pointer to next token
 */
typedef struct s_tokens
{
	t_type			type;
	char			*str;
	struct s_tokens	*next;
}t_tokens;

/**
 * state machine control struct
 * @param state current state
 * @param status current status
 * @param tokens_list list of tokens
 * @param cmd command line copied from t_data
 * @param count current position in cmd
 * @param start used to set everytime a non-"metachar"
 * is first found in order to get the strings
 * @param len counter used once start is set 
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
	int			exit_code;
}t_state_machine;

/**
 * state machine that will that the command_line contained inside
 * the data struct and break it into tokens
 * @param mini_data data struct
 */
int		parse_machine(t_data *mini_data, t_state_machine *parser);
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
int	parse_tokens(t_state_machine *parser, t_data *mini_data);
/**
 * prints syntax error, set exit code to 258 and free token list
 * @param parser state machine 
 * @param c character that triggered the error
*/
void	syntax_error(t_state_machine *parser, char c);
/**
 * prints quotes syntax error, set exit code to 258 and free token list
 * @param parser state machine 
*/
void	unclosed_error(t_state_machine *parser);
/**
 * main parser function
*/
int		parse(t_data *mini_data);
/**
 * creates a temporary folder with the content given to STDIN.
 * STDIN remains open with readline until the given limiter is found.
 * @param it_token pointer to the list of tokens
 * @param cmd cmd node 
 * @param mini_data main struct where the command list is going to be stored
 */
void	handle_heredoc(t_tokens **it_token, t_commands **cmd, \
		t_data *mini_data);
/**
 * Allocate memory for a quoteless string, coppy given string ignoring quotes
 * @param str 
 * @return char* unquoted string
 */
char	*remove_quotes(char *str);

#endif //MINISHELL_LEXICAL_ANALYZER_H
