/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/26 10:05:05 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/param.h>
# include "minishell.h"

/* BUILTINS */
/**
 * checks if the first cmd is a builtin and redirects to the right 
 * function accordingly or returns with 1 if not a builtin
 * @param cmd splitted command line
 * @param str entire command line un-splitted
 * @param mini 
 */
int		builtins(char **cmd, char *str, t_data *mini);
/**
 * checks if the first cmd is a builtin if so it returns 0 else returns 1
 * @param cmd splitted command line
 */
int		check_builtins(char **cmd);

/**
 * looks for the position of the arg(s) to be unsetted in envp
 * @param arg splitted command line
 * @param mini
 */
int		builtin_unset(t_data *mini, char **arg);
/**
 * loops through envp to find the specified arg
 * @param arg arg/var to be unset
 * @param mini to access mini->mini_envp
 */
int		find_envp(t_data *mini, char *arg);
/**
 * updates the environement list/array by malloc-ing a new array and skipping
 * over the arg to be unset, and returns the new malloc-ed array
 * @param envp current environement array
 * @param arg arg to be unset from the array
 * @param size size of current array -1 for the arg to be unset
 */
char	**update_envp(char **envp, char *arg, int size);

/**
 * prints the current working directory on the terminal via getcwd
 * @param mini
 */
int		builtin_pwd(t_data *mini);

/**
 * checks if the variable is valid to be exported or not, if not
 * it redirects to an error function
 * @param cmd splitted command line
 * @param str entire command line un-splitted
 * @param mini
 */
int		builtin_export(t_data *mini, char **cmd, char *str);
/**
 * checks if the variable is valid to be exported or not, and if it 
 * contains specific characters or quotes
 * @param cmd splitted command line
 */
bool	check_cmd(char *cmd);
/**
 * loops through the variable to see if it contains a dollar sign or quotes
 * @param cmd splitted command line
 */
bool	is_valid_noerror(char *cmd);
/**
 * loops through the string to see to find the position of the equal sign
 * @param cmd splitted command line
 */
int		len_equal(char *cmd);
/**
 * mallocs a new envp array and adds one extra line to it, it copies over the
 * existing envp array to the new one and adds the new variable to export to the array
 * then null terminates the array and frees the old envp array
 * @param envp current environement list from mini->mini_envp
 * @param cmd variable to export
 * @param mini
 */
char	**add_line_envp(char **envp, char *cmd, t_data *mini);
/**
 * prints the current envp list with "declare -x" in front of each var
 * @param mini
 */
void	print_xenv(t_data *mini);
/**
 * in case the var to be exported already exists in the envp array, with this function we
 * overwrite what comes after the equal sign to the new given value
 * @param mini
 * @param name name of the var (before the equal sign)
 * @param res expansion of the var (after the equal sign)
 */
int		replace_envp_var(t_data *mini, char *name, char *res);

/**
 * checks exit comes with a numeric argument, if so we exit the program with the 
 * modulo of 256 of the given argument, else we exit with the lastest exit_code that
 * has been set
 * @param cmd splitted command line
 * @param mini 
 */
void	builtin_exit(t_data *mini, char **cmd);

/**
 * prints the envp array list
 * sets the exit_code to 0 if all went well, then returns with the exit_code
 * @param cmd splitted command line
 * @param mini 
 */
int		builtin_env(t_data *mini, char **cmd);

/**
 * checks if there is a "-n" flag if so it won't add a new line at the end; and in both
 * cases it will print out everything that comes after echo (with or without new line)
 * sets the exit_code to 0 if all went well, then returns with the exit_code
 * @param cmd splitted command line
 * @param str command line as one long string
 * @param mini 
 */
int		builtin_echo(t_data *mini, char **cmd, char *str);

/**
 * checks if there is an argument after cd, else will change the directory to HOME
 * in case there is an argument it send it to the function search_specific_path();
 * sets the exit_code to 0 if all went well, then returns with the exit_code
 * @param cmd splitted command line
 * @param mini 
 */
int		builtin_cd(t_data *mini, char **cmd);
/**
 * checks if the arg is a valid diretory (else throws an error), then changes to directory
 * to the new one and updates the PWD with the new directory and the OLDPWD with 
 * the previous directory within the envp array
 * sets the exit_code to 0 if all went well
 * @param cmd cmd[1], which is the arg coming after cd
 * @param mini 
 */
int		search_specific_path(t_data *mini, char *cmd);
/**
 * updates the OLDPWD with the previous directory within the envp array
 * sets the exit_code to 0 if all went well
 * @param mini 
 */
int		change_oldpwd(t_data *mini);
/**
 * updates the PWD with the current/new directory within the envp array
 * sets the exit_code to 0 if all went well
 * @param mini 
 */
int		change_pwd(t_data *mini);
/**
 * loops through the envp array list looking for HOME=
 * when found it returns the expansion of HOME (what comes after the equal sign)
 * else returns NULL if not found
 * @param mini 
 * @param target which is equal to HOME 
 */
char	*search_path(t_data *mini, char *target);

/* EXEC */
/**
 * starting point of the exectutor
 * counts the number of commands with the command line
 * if no commands and only in/out files it open/closes/creates them when necessary 
 * if only one or more command(s) it redirects to another function
 * then it frees the splitted command lists and unlinks/remove the tmp_file from heredoc
 * in case it was created
 * then return with the set exit_code
 * @param mini
 */
int		start(t_data *mini);

/**
 * closes the two ends of the fd based on the amount of commands
 * @param fd 
 * @param nb number of commands
 */
void	close_pipe(int **fd, int nb);
/**
 * closes the in/out file if any
 * @param mini
 */
void	close_fds(t_data *mini);
/**
 * callocs fd[2] based on the amount of commands and then creates pipes for it
 * @param mini
 */
int		**open_pipes(t_data *mini);

/**
 * returns the size of the given list
 * @param lst
 */
int		lst_size(t_commands *lst);
/**
 * frees a double array
 * @param str
 */
void	free_str(char **str);
/**
 * loops through the list and returns the last positions
 * @param lst
 */
t_pid	*pid_lstlast(t_pid *lst);
/**
 * loops through the list and adds content to the last node
 * @param lst list to loop through
 * @param content content/data to be added
 */
void	pid_lstadd_back(t_pid **lst, pid_t content);
/**
 * loops through the list and frees the fd's
 * @param fd
 * @param nb_cmds number of commands
 */
void	free_fd(int **fd, int nb_cmds);
/**
 * loops through the array and returns its size
 * @param envp environement list
 */
int		array_size(char **envp);
/**
 * set the exit_code within mini to the value of code
 * @param mini
 * @param code exit code to be set
 */
void	set_exit_code(t_data *mini, int code);
/**
 * loops through the array and returns its size
 * @param mini environement list
 */
int		size_envp(t_data *mini);
/**
 * checks if the string contains only alpha-numeric values, if so it returns 0
 * and if it encounters non alpha-numeric values returns 1
 * @param str given string
 */
int		not_alphanum(char *str);
/**
 * loops through the envp array, searching for PATH= and return its position 
 * in the array, if not found returns -1
 * @param envp environement list
 */
int		find_path(char **envp);

/**
 * checks if the given command is a builtin, if so it sends it to the right function
 * else it checks if envp is not NULL and if there is a path to the command (else 
 * throws an error); if there is a path to the command it will look up that path 
 * and try to execve the command.
 * @param envp environement list
 * @param mini
 * @param cmd splitted command line
 */
char	*split_args(char *cmd, char **envp, t_data *mini);

/**
 * first tries to open in/out files if any (and check if the returned -1, if so exits with 1),
 * then dup2 the in/out file to STDIN_FILENO/STDOUT_FILENO, and then calls the split_args()
 * funtion
 * @param mini
 */
void	run_one_cmd(t_data *mini);
/**
 * first creates one fork, then ignore_signals(), cheks if the fork failed if not in the child
 * process it unset_signals() and run_one_cmd(). once that done closes the pipes, frees the fd
 * and return with the latest exit_code.
 * @param mini
 */
int		exec_fork_onecmd(t_data *mini);

/**
 * checks if any outfiles, if not set the file number to 1/STDOUT_FILENO;
 * if there are outfiles, checks the type if its append or overwrite and accordingly opens the
 * outfile (creates it if not existant), and goes on until all given outfiles have been opened.
 * only the last outfile remains open, the rest is closes.
 * exit_code set to 0 of all went well.
 * @param commands to store the file's file number
 * @param mini
 */
void	output_re(t_commands *commands, t_data *mini);

/**
 * checks if any infiles, if not set the file number to 0/STDIN_FILENO;
 * if there are infiles opens them, and goes on until all given infiles have been opened.
 * only the last outfile remains open, the rest is closes.
 * exit_code set to 0 of all went well.
 * @param commands to store the file's file number
 * @param mini
 */
void	input_re(t_commands *commands, t_data *mini);

/**
 * prints out the given error message from str
 * @param cmd command related to the error
 * @param str error message
 */
void	err_msg(char *cmd, char *str);
/**
 * prints out the given error message from str, and sets the exit code to 0
 * @param mini
 * @param str error message
 */
void	error_msg(char *str, t_data *mini);
/**
 * checks the str for quotes and dollar sign to see if something needs to be expanded,
 * if not it returns the strdup of the str.
 * @param mini_data
 * @param str string to check if vars to be expanded or not
 */
char	*expanded(char *str, t_data *mini_data);
/**
 * locates the dollar sign, and returns the the expanded line
 * @param mini
 * @param line string to be expanded
 */
char	*expand_dollar(char *line, t_data *mini);
/**
 * checks the lenght of the expansion, 
 * @param start starting point of the expansion
 * @param line string to be expanded
 */
int		var_len(char *line, int start);
/**
 * isolates the variable name and adds an equal sign after it, and returns the name + equal sign
 * @param start starting point of the expansion name
 * @param end starting point of the expansion name
 * @param line string to be expanded
 */
char	*var_name(char *line, int start, int end);
/**
 * loops through the environement looking for var, and then returns what string that the var
 * should expand to (without the name and equal sign in it)
 * if not found returns an empty string
 * @param var 
 * @param mini
 */
char	*search_envp(char *var, t_data *mini);
/**
 * isolates the var to be expanded, then removed the var name and replaces it with the expansion,
 * and returns the new expanded string
 * @param line complete string to be expanded 
 * @param var_exp the expansion of the variable 
 * @param start start of the var name
 * @param end end of the var name
 */
char	*var_replace(char *line, char *var_exp, int start, int end);
/**
 * isolates the var to be expanded, then removed the var name and replaces it with the expansion,
 * and returns the new expanded string
 * @param line complete string to be expanded 
 * @param mini
 * @param start start of the var name
 */
char	*char_expand_var(char *line, t_data *mini, int start);

/**
 * opens as many pipe(f_fd) as there are commands -1, sends to forkfork() for dup2's
 * then connects the fds accordingly to set the read_end correctly for the next command
 * and for the last command exec_last_cmd()
 * and then pid_exit_code in order to exit and return with the right exit_code
 * @param mini
 */
int		exec_fork(t_data *mini);
/**
 * waitpid until all the child process have finished, and then sets the right exist code
 * also checking if there was a signal that interfeered or not
 * @param mini
 * @param pid to check on child processes completion
 */
void	pid_exit_code(t_data *mini, pid_t pid);
/**
 * creates a fork, ignore_signals and add the PID number to the end our our pid list
 * then in the child process unsets the signals and sends the command to childchild();
 * @param mini
 * @param commands
 * @param read_end
 * @param p_fd
 */
int		forkfork(t_data *mini, t_commands *commands, int read_end, int *p_fd);
/**
 * closes p_fd[0], and dup3 the read_end to the STDIN_FILENO and p_fd[1] to STDOUT_FILENO
 * then sends the command to split_args() and closes p_fd[1]
 * @param mini
 * @param commands
 * @param read_end
 * @param p_fd
 */
void	childchild(t_data *mini, t_commands *commands, int read_end, int *p_fd);

#endif