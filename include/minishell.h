//
// Created by laura on 11-6-23.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <signal.h>
#include <stdbool.h>

typedef enum s_type
{
    T_WHITESPACE,
    T_PIPE,
    T_BIG,
    T_BIGBIG,
    T_SMALL,
    T_SMALLSMALL,
    T_CHAR,
    T_END,
}t_type;
/**
 * list of child PIDs
 */
typedef struct s_pid
{
    pid_t pid;
    struct s_pid *next;
}t_pid;

/**
 * list of environment variables
 * @name given name of the variable
 * @content content of the variable
 * @next next variable
 */
typedef struct s_env_args
{
    char *name;
    char *content;
    struct s_env_args *next;
}t_env_args;

/**
<<<<<<< HEAD
 *
 * @param str
 * @next
 *
=======
 * @param status true if valid, false if error was found
 * @param type type of token
 * @param str tolken
 * @param next pointer to next tolken
>>>>>>> 6b6bf631dbea0ae153cf54321488ef9e3c32cd25
 */
typedef struct s_tokens
{
    t_type  type;
    char *str;
    struct s_tokens *next;
}t_tokens;

typedef struct s_tokens_point
{
	int len;
	char *start;
	t_type type;
	struct s_tokens_point *next;
}t_token_point;

/**
 * Main struct with all the information that is needed to run
 * the commands given to minishell
 * @amount_of_tolkens how many item on the tolken list and 2D
 * array
 * @tolkens tolkens XD
 * @env_arg list of environment variables
 * @command_line original command line
 */
typedef struct s_data
{
    char **mini_envp;
    t_tokens *tokens_list;
    t_env_args *env_args;
	t_token_point *token_point;
    char *command_line;
}t_data;



#endif //MINISHELL_MINISHELL_H
