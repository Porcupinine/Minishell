
#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

typedef enum S_REDIRECT
{
	REDIRECT_INPUT,
	HEREDOC,
	REDIRECT_OUTPUT,
	APPEND_OUTPUT,
}T_REDIRECT;
/**
 * list of child PIDs
 */
typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}t_pid;

/**
 * list of outfiles
 * @param file name of the outfile
 * @param tyoe type of redirection, hold specific values
 * set by open function
 * @param next pointer to the next item on the list
 */
typedef struct s_outfile
{
	char				*file;
	T_REDIRECT			type;
	struct s_outfile	*next;
}t_outfile;

/**
 * list of infiles
 * @param file name of the file to read from
 * or safe-word in case it is a heredoc redirection
 * @param type type os redirection, hold specific values
 * set by open function
 * @param next pointer to the next item on the list
 */
typedef struct s_infile
{
	char			*file;
	T_REDIRECT		type;
	struct s_infile	*next;
}t_infile;

/**
 * list that holds all parsed commands from the current
 * command line if non existent, values must be set to NULL
 * @param cmd command to be processed
 * @param t_outfile list of outfile redirections that
 * must be applied to the command
 * @param t_infile list of infile redirections that
 * must be applied to the command
 * @param in
 * @param out
 * @param fd
 * @param nb_cmds
 * @param status
 * @param next pointer for the next item on the list
 */
typedef struct s_commands
{
	char				*cmd;
	t_outfile			*outfiles;
	t_infile			*infiles;
	int					out;
	int					in;
	int					**fd;
	int					nb_cmds;
	int					status;
	struct s_commands	*next;
}t_commands;

/**
 * list of environment variables
 * @name given name of the variable
 * @content content of the variable
 * @next next variable
 */
typedef struct s_env_args
{
	char				*name;
	char				*content;
	struct s_env_args	*next;
}t_env_args;

typedef struct s_mini_envp_list
{
	char					*str;
	struct s_mini_envp_list *next;
}t_mini_envp_list;

/**
 * Main struct with all the information that is needed to run
 * the commands given to minishell
 * @param mini_envvp copy of envpp
 * @param cmds list of commands
 * @param command_line command line that was given
 * @param t_commands
 * @param process
 */
typedef struct s_data
{
	char			**mini_envp;
	t_commands		*cmds;
	t_env_args		*env_args;
	t_mini_envp_list *mini_envp_list;
	char			*command_line;
	t_commands		*commands;
	t_pid			*process;
//	int 			exit_code;
}t_data;

#endif //MINISHELL_MINISHELL_H
