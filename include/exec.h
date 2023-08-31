/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/31 16:21:37 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "minishell.h"

/* BUILTINS */
int		builtins(char **cmd, t_data *mini);
int		check_builtins(char **cmd);

int		builtin_unset(t_data *mini, char **arg);
int 	find_envp(t_data *mini, char *arg);
char 	**update_envp(char **envp, char *arg, int size);

int		builtin_pwd(t_data *mini);

int		builtin_export(t_data *mini, char **cmd);
bool	check_cmd(char *cmd);
bool	is_valid_noerror(char *cmd);
int		len_equal(char *cmd);

void	builtin_exit(t_data *mini, char **cmd);

int		builtin_env(t_data *mini, char **cmd);

int		builtin_echo(t_data *mini, char **cmd);

int		builtin_cd(t_data *mini, char **cmd);
int		search_specific_path(t_data *mini, char *cmd);
int		change_oldpwd(t_data *mini);
int		change_pwd(t_data *mini);
char	*search_path(t_data *mini, char *target);


/* EXEC */
int		start(t_data *mini);

void	close_pipe(int **fd, int nb);
void	close_fds(t_data *mini);
int	    **open_pipes(t_data *mini);

int		lst_size(t_commands *lst);
void	free_str(char **str);
t_pid	*pid_lstlast(t_pid *lst); // USING??
void	pid_lstadd_back(t_pid **lst, pid_t content); // USING??
void	free_fd(int **fd, int nb_cmds);
int		array_size(char **envp);
void	set_exit_code(t_data *mini, int code);
int		size_envp(t_data *mini);
int		not_alphanum(char *str);
int     find_path(char **envp);

char	*split_args(char *cmd, char **envp, t_data *mini);

void	run_one_cmd(t_data *mini);
void    child_dup2(t_data *mini, t_commands *commands, int i, int pos);

void    output_re(t_commands *commands);

void	input_re(t_commands *commands, t_data *mini);

int	    cmd_err(char *str, int error); // USING??
void	builtin_err(char *cmd, char *str); // USING??
void	err_msg(char *cmd, char *str); // combine with the above ?? // USING??
void	builtin_err2(char *cmd, char *arg, char *str); // USING??
void	err_cmd_not_found(char **command); // USING??
void	error_msg(char *str, t_data *mini); // USING??

char	*expand_dollar(char *line, t_data *mini);
int 	expand_var(char **line, t_data *mini, int start);
int 	var_len(char *line, int start);
char 	*var_name(char *line, int start, int end);
char 	*search_envp(char *var, t_data *mini);
char	*var_replace(char **line, char *var_exp, int start, int end);

int		exec_fork_onecmd(t_data *mini);
int	    exec_fork(t_data *mini, int nb_cmds);

#endif