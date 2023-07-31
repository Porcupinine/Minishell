/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:43:48 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 15:00:03 by dmaessen         ###   ########.fr       */
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

int		builtin_unset(t_data *mini, char **arg);
int 	find_envp(t_data *mini, char *arg);
int		size_envp(t_data *mini); // maybe put in a utils??
char 	**update_envp(char **envp, char *arg, int size);

int		builtin_pwd(t_data *mini);

int		builtin_export(t_data *mini, char *cmd);

void	builtin_exit(t_data *mini, char *cmd);

int		builtin_env(t_data *mini, char **cmd);

int		builtin_echo(t_data *mini, char *cmd);

int		builtin_cd(t_data *mini, char *cmd);
int		search_path_cd(t_data *mini);
int		change_oldpwd(t_data *mini);
int		change_pwd(t_data *mini);


/* EXEC */
int		start(t_data *mini);
void	close_pipe(int **fd, int nb);

t_pid	*pid_lstlast(t_pid *lst); // USING??
void	pid_lstadd_back(t_pid **lst, pid_t content); // USING??
int		lst_size(t_commands *lst); // USING??

char	*split_args(char *cmd, char **envp, t_data *mini);

void	which_child(t_data *mini, int i, int pos);

void	output_re(t_data *mini);

void	input_re(t_data *mini);
void	read_stdin(t_data *mini);

int	    cmd_err(char *str, int error);
void	builtin_err(char *cmd, char *str);
void	builtin_err2(char *cmd, char *arg, char *str);

char	*expand_dollar(char *line, t_data *mini); // USING??
bool	dollar_check(t_data *mini); // USING

#endif