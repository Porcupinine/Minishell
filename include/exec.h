/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/15 15:30:17 by dmaessen         ###   ########.fr       */
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
int		check_builtins(char **cmd, t_data *mini);

int		builtin_unset(t_data *mini, char **arg);
int 	find_envp(t_data *mini, char *arg);
int		size_envp(t_data *mini); // maybe put in a utils??
char 	**update_envp(char **envp, char *arg, int size);

int		builtin_pwd(t_data *mini);

int     builtin_export(t_data *mini, char **cmd);

void	builtin_exit(char *cmd); // t_data *mini,  needed ??

int		builtin_env(t_data *mini, char **cmd);

int		builtin_echo(t_data *mini, char **cmd);

int		builtin_cd(t_data *mini, char **cmd);

/* EXEC */
int		start(t_data *mini);
void	close_pipe(int **fd, int nb);
void	close_fds(t_data *mini);

int		lst_size(t_commands *lst);
void	free_str(char **str);
t_pid	*pid_lstlast(t_pid *lst); // USING??
void	pid_lstadd_back(t_pid **lst, pid_t content); // USING??
void	free_fd(int **fd, int nb_cmds);

char	*split_args(char *cmd, char **envp, t_data *mini);

void	which_child(t_data *mini, t_commands *commands, int i, int pos);
void	run_one_cmd(int in_file, int out_file, t_data *mini); // check

void    output_re(t_commands *commands);

void    input_re(t_commands *commands, t_data *mini);
void	read_stdin(t_commands *commands, t_data *mini);

int	    cmd_err(char *str, int error);
void	builtin_err(char *cmd, char *str);
void	err_msg(char *cmd, char *str); // combine with the above ??
void	builtin_err2(char *cmd, char *arg, char *str);
void	err_cmd_not_found(char **command);

char	*expand_dollar(char *line, t_data *mini);
int 	expand_var(char **line, t_data *mini, int start);
int 	var_len(char *line, int start);
char 	*var_name(char *line, int start, int end);
char 	*search_envp(char *var, t_data *mini);
char	*var_replace(char **line, char *var_exp, int start, int end);

int		exec_fork_onecmd(t_data *mini);

#endif