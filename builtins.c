/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/19 13:00:08 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

void ft_exit(int error)
{
	strerror(error);
	exit(error);
}

/*
	should it also handle echo $?  ??
	example to deal with the $ARG/$PATH expantion: printf("PATH : %s\n", getenv("PATH"));
	// one extra else if in case non-accepted flags, or does laura handle upfront?
	// for both handle the $ or not ?? think so
	// check if quotes
		// if yes check if they are closed
		// else needs to read from stdin
*/
void	builtin_echo(t_data *mini_data)
{
	// Laura deals with quotes situation
	if (ft_strncmp(mini_data->token[1], "echo -n", 7) == 0) // probably if flag for echo or not instead of strncmp
		printf("%s", mini_data->token[1] + 8);
		// just printf the str (from struct) without new line
	else
		printf("%s\n", mini_data->token[1] + 5);
		// just printf the str (from struct) without new line
	// we could also have some $ in there to deal with
		// if flag is on, deal with it else echo direcly
	return (0); // check
}

// bool	check_quotes(t_data *mini_data)
// {
// 	int i;
// 	bool s_quotes;
// 	bool d_quotes;

// 	i = 0;
// 	s_quotes = false;
// 	d_quotes = false;
// 	while (mini_data->str[i])
// 	{
// 		if (mini_data->str[i] == 34 && d_quotes == false) // double
// 			d_quotes == true;
// 		if (mini_data->str[i] == 34 && d_quotes == true)
// 			d_quotes == false;
// 		if (mini_data->str[i] == 39 && s_quotes == false) // single
// 			s_quotes == true;
// 		if (mini_data->str[i] == 39 && s_quotes == true)
// 			s_quotes == false;
// 		i++;
// 	}
// 	if (d_quotes == true || s_quotes == true 
// 		|| (d_quotes == true && s_quotes == true)) // as could be both d && s that are true
// 		return (true);
// 	return (false);
// }

/*
	abs path describe the location from the root directory
	relative path takes you below your current one

	if only cd --> takes you back to home directory
	if cd . --> don't implement
	if cd .. --> don't implement
	if cd ../../.. --> check if backslash present else add it yoruself
	if cd xx/ --> check if backslash present else add it yoruself
*/
void	builtin_cd(t_data *mini_data)
{
	int i;
	struct stat info;
	
	if (ft_strchr(mini_data->tokens.str[0], "cd\0")) // bring back to home directory // condition: if no flag
	{
		i = 0;
		while (mini_data->mini_envp[i])
		{
			if (ft_strncmp(mini_data->mini_envp[i], "HOME=", 5) == 0) // all good also if unset HOME as should error
				break ;
			i++;
		}
		if (chdir(mini_data->mini_envp[i] + 5) != 0)
			return (ft_exit(errno)); // check
		return (0); // check
	}
	else // a specified path
	{
		if (lstat(mini_data->token.str[0], &info) == 0) // do something if != 0 ??
		{
			if (S_ISDIR(info.st_mode)) // check if the path leads is a directory
			{
				if (mini_data->token.str[0][ft_strlen(mini_data->token.str)] != "/")
					mini_data->token.str[0] = ft_strjoin(mini_data->token.str[0], "/");
			}	
		}
		if (chdir(mini_data->token.str[0]) != 0)
			return (ft_exit(errno)); // check
		return (0); // check
	}
	builtin_pwd(mini_data); // FOR TEST -- RM AFTER
}

void	builtin_pwd(t_data *mini_data)
{
	char *pwd_path;

	pwd_path = malloc((PATH_MAX + 1) * sizeof(char)); // or MAXPATHLEN ?? instead of PATH_MAX
	if (pwd_path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (getcwd(pwd_path, PATH_MAX + 1) == NULL)  // or MAXPATHLEN ?? instead of PATH_MAX
		return (ft_exit(errno)); // check this exit tho
	printf("%s", pwd_path);
	free(pwd_path);
	return (0);
}

/*
	using export should add the mentionned variable to envp
	(not the same as our local arg list)

	// export a variable
	// do we support the = something ??
	// access envp
	// open with write rights and add a line for it
*/
void	builtin_export(t_data *mini_data)
{
	int end;

	end = 0;
	if (*mini_data->mini_envp == NULL)
		return (ft_exit(errno));
	while (!mini_data->mini_envp[end])
		end++;
	// either
	ft_lstadd_back(); // make our own ft for it tho to allocate the content of it already
	// or
	
	// all depends if we use an array or a linekd list here
	// do i need to malloc the line ? PROBABLY YES
}

/* 
	unset: values and attributes of variables and functions
	Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.
	via envp (PATH and SHELL)?? --> look in the shell + the list created by laura
	maybe getenvp then unlink
	and for attributes/var ??
*/
static t_env_args *search_args(t_env_args *env_args, char *arg)
{
	while (env_args->next != NULL)
	{
		if (env_args->name == arg)
			return (&env_args); 
		env_args = env_args->next;
	}
	return (NULL);
}

static void del_args(t_env_args *env_args)
{
	t_env_args *temp;
	
	temp = env_args->next;
	env_args->name = env_args->next->name;
	env_args = temp;
	free(temp);
}

void	builtin_unset(t_data *mini_data) 
{
	char *arg;
	char *path;
	t_env_args *temp;
	
	arg = ft_substr(mini_data->tolkens->str, ft_strlen("unset "), ft_strlen(mini_data->tolkens->str)); // str in a certain position tho..
	// ABOVE IS WRONG JUST TAKE NEXT ARG IN LIST AFTER 'UNSET'
	if (arg == NULL || arg == "_") // as the underscore cannot be unset, but not an error tho for underscore??
		return (ft_exit(errno)); // check this exit tho
	// need to check if only 1 word tho or not?
	path = getenv(arg);
	if (path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (unlink(path) == 0) // search the ones given by shell
		return (0);
	// but doesn't work on directories i believe ..
	else // search OUR list
	{
		if (search_args(&mini_data->env_args, arg) != NULL)
		{
			del_args(search_args(&mini_data->env_args, arg)); // check if my logic is correct
			return (0);
		}
	}
	return (ft_exit(errno)); // meaning not found
}

void	builtin_env(t_data *mini_data)
{
	int i;

	if (*mini_data->mini_envp == NULL)
		return (ft_exit(errno));
	i = 0;
	while (mini_data->mini_envp[i])
	{
		printf("%s\n", mini_data->mini_envp[i]);
		i++;
	}
	return (0);
}

void	builtin_exit(t_data *mini_data)
{
	// int status;
	printf("exit\n");
	exit(0); 
	// cjeck if we need to free things before closing the program
	// or with another status, but which one then??
}

void	builtins(char **argv, char **envp, t_data *mini_data) // still incomplete (envp needed)
{
	if (ft_strncmp(argv[1], "echo", 4) == 0) // change the argv[1] part (depending on struct)
		builtin_echo(mini_data);
	else if (ft_strncmp(argv[1], "cd", 2) == 0) // change the argv[1] part (depending on struct)
		builtin_cd();
	else if (ft_strncmp(argv[1], "pwd", 3) == 0) // change the argv[1] part (depending on struct)
		builtin_pwd(envp);
	else if (ft_strncmp(argv[1], "export", 6) == 0) // change the argv[1] part (depending on struct)
		builtin_export();
	else if (ft_strncmp(argv[1], "unset", 5) == 0) // change the argv[1] part (depending on struct)
		builtin_unset();
	else if (ft_strncmp(argv[1], "env", 3) == 0) // change the argv[1] part (depending on struct)
		builtin_env(mini_data);
	else if (ft_strncmp(argv[1], "exit", 4) == 0) // change the argv[1] part (depending on struct)
		builtin_exit(mini_data);
		// can't we just use the "real exit" function here, and leave the shell?
}

// void builtins()
// {
// 	// maybe to the same way laura constructed her function void thing-y
// }
