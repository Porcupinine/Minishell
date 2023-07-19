/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:32:57 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:34:24 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>

#define append_output "O_APPEND | O_CREAT | O_WRONLY | O_TRUNC"
#define redirect_output "O_CREAT | O_WRONLY | O_TRUNC"
#define redirect_infile "O_RDONLY"
#define heredoc "O_CREAT | O_WRONLY | O_TRUNC"

/**
 * list of child PIDs
 */
typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}t_pid;

/**
 *
 */
typedef struct s_outfile
{
	char *file;
	char *type; // give one of the defines
	struct s_outfile *next;
}t_outfile;

typedef struct s_infile
{
	char *file;
	char *type;

}t_infile;

typedef struct s_commands
{
	char *cmd;
	t_outfile *outfiles;
	t_infile  *infiles;
	struct s_commands *next;
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
 * @amount_of_tolkens how many item on the tolken list and 2D
 * array
 * @tolkens tolkens XD
 * @env_arg list of environment variables
 * @command_line original command line
 */
typedef struct s_data
{
	char		**mini_envp;
	t_commands 	*cmds;
	t_env_args	*env_args;
	char		*command_line;
}t_data;

#endif //MINISHELL_MINISHELL_H
