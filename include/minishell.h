/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:32:57 by laura             #+#    #+#             */
/*   Updated: 2023/07/31 15:00:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>
#include <fcntl.h>

#define APPEND_OUTPUT (O_APPEND | O_CREAT | O_WRONLY | O_TRUNC) //1601
#define REDIRECT_OUTPUT (O_CREAT | O_WRONLY | O_TRUNC) //577
#define REDIRECT_INPUT (O_RDONLY) // 0
#define HEREDOC (O_CREAT | O_WRONLY | O_TRUNC) //577

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
	char				*file;
	int 				type;
	struct s_outfile	*next;
}t_outfile;

typedef struct s_infile
{
	char			*file;
	unsigned short 				type;
	struct s_infile *next;
}t_infile;

typedef struct s_commands
{
	char 		*cmd;
	t_outfile 	*outfiles;
    int 		out;
	t_infile  	*infiles;
    int 		in;
	int			**fd;
	int			nb_cmds;
	int			status;
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
	t_commands	*cmds;
	t_env_args	*env_args;
	char		*command_line;
    t_commands  *commands;
	t_pid		*process;
}t_data;

#endif //MINISHELL_MINISHELL_H
