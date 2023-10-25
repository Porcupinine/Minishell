/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/25 23:12:48 by domi             ###   ########.fr       */
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

char	*split_args(char *cmd, char **envp, t_data *mini);

void	run_one_cmd(t_data *mini);
int		exec_fork_onecmd(t_data *mini);

void	output_re(t_commands *commands, t_data *mini);

void	input_re(t_commands *commands, t_data *mini);

void	err_msg(char *cmd, char *str);
void	error_msg(char *str, t_data *mini);
char	*expanded(char *str, t_data *mini_data);
char	*expand_dollar(char *line, t_data *mini);
void	expansions(char *commands);
int		expand_var(char **line, t_data *mini, int start);
int		var_len(char *line, int start);
char	*var_name(char *line, int start, int end);
char	*search_envp(char *var, t_data *mini);
char	*var_replace(char *line, char *var_exp, int start, int end);
char	*char_expand_var(char *line, t_data *mini, int start);

int		exec_fork(t_data *mini);
void	pid_exit_code(t_data *mini, pid_t pid);
int		forkfork(t_data *mini, t_commands *commands, int read_end, int *p_fd);
void	childchild(t_data *mini, t_commands *commands, int read_end, int *p_fd);

#endif