/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/07 12:12:45 by domi             ###   ########.fr       */
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
 * 
 * @param cmd splitted command line
 * @param str entire command line un-splitted
 * @param mini
 */
int		builtin_export(t_data *mini, char **cmd, char *str);
bool	check_cmd(char *cmd);
bool	is_valid_noerror(char *cmd);
int		len_equal(char *cmd);
char	**add_line_envp(char **envp, char *cmd, t_data *mini);
void	print_xenv(t_data *mini);
int		replace_envp_var(t_data *mini, char *name, char *res);

void	builtin_exit(t_data *mini, char **cmd);

int		builtin_env(t_data *mini, char **cmd);

int		builtin_echo(t_data *mini, char **cmd, char *str);

int		builtin_cd(t_data *mini, char **cmd);
int		search_specific_path(t_data *mini, char *cmd);
int		change_oldpwd(t_data *mini);
int		change_pwd(t_data *mini);
char	*search_path(t_data *mini, char *target);

/* EXEC */
int		start(t_data *mini);

void	close_pipe(int **fd, int nb);
void	close_fds(t_data *mini);
int		**open_pipes(t_data *mini);

int		lst_size(t_commands *lst);
void	free_str(char **str);
t_pid	*pid_lstlast(t_pid *lst);
void	pid_lstadd_back(t_pid **lst, pid_t content);
void	free_fd(int **fd, int nb_cmds);
int		array_size(char **envp);
void	set_exit_code(t_data *mini, int code);
int		size_envp(t_data *mini);
int		not_alphanum(char *str);
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