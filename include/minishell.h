/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:32:57 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 12:03:44 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>

/*Defined flags to be used as type for outfiles and infiles */
# define APPEND_OUTPUT (O_APPEND | O_CREAT | O_WRONLY | O_TRUNC) //1601
# define REDIRECT_OUTPUT (O_CREAT | O_WRONLY | O_TRUNC) //577
# define REDIRECT_INPUT (O_RDONLY) // 0
# define HEREDOC (O_CREAT | O_WRONLY | O_TRUNC) //577

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
	int					type;
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
	unsigned short	type;
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
	char		**mini_envp;
	t_commands	*cmds;
	t_env_args	*env_args;
	char		*command_line;
	t_commands	*commands;
	t_pid		*process;
}t_data;

#endif //MINISHELL_MINISHELL_H
