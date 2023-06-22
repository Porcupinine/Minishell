/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/22 16:12:39 by dmaessen         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/stat.h>

/* 
file for the buildins:
    ◦ echo with option -n
    ◦ cd with only a relative or absolute path
    ◦ pwd with no options
    ◦ export with no options
    ◦ unset with no options
    ◦ env with no options or arguments
    ◦ exit with no options
*/

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
*/
void	builtin_echo(char **argv) // or command (check struct naming)
{
	if (ft_strncmp(argv[1], "echo -n", 7) == 0)
		printf("%s", argv[2]);
	else
		printf("%s\n", argv[2]);
	
	return (0); // check
}

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
	
	if (ft_strchr(mini_data->tokens.str[0], "cd\0")) // bring back to home directory
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
}

void	builtin_pwd(t_data *mini_data) // ft getcwd ?? or via envp "PWD=" not an option if path unset
{
	char *pwd_path;

	pwd_path = malloc((PATH_MAX + 1) * sizeof(char));
	if (pwd_path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (getcwd(pwd_path, PATH_MAX + 1) == NULL)
		return (ft_exit(errno)); // check this exit tho
	printf("%s\n", pwd_path);
	free(pwd_path);
	return (0);	// return or exit? "The pwd utility exits 0 on success, and >0 if an error occurs."
}

void	builtin_export()
{
	// export a variable
	// do we support the = something ??
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
	if (arg == NULL)
		return (ft_exit(errno)); // check this exit tho
	// need to check if only 1 word tho or not?
	path = getenv(arg);
	if (path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (unlink(path) == 0) // search the ones given by shell
		return (0);
	else // search OUR list
	{
		if (search_args(&mini_data->env_args, arg) != NULL)
		{
			del_args(search_args(&mini_data->env_args, arg));
			return (0);
		}
	}
	return (ft_exit(errno)); // meaning not found
}

void	builtin_env()
{
	
}

void	builtin_exit()
{
	
}

void	builtins(char **argv, char **envp) // still incomplete (envp needed)
{
	if (ft_strncmp(argv[1], "echo", 4) == 0) // change the argv[1] part (depending on struct)
		builtin_echo(argv);
	else if (ft_strncmp(argv[1], "cd", 2) == 0) // change the argv[1] part (depending on struct)
		builtin_cd();
	else if (ft_strncmp(argv[1], "pwd", 3) == 0) // change the argv[1] part (depending on struct)
		builtin_pwd(envp);
	else if (ft_strncmp(argv[1], "export", 6) == 0) // change the argv[1] part (depending on struct)
		builtin_export();
	else if (ft_strncmp(argv[1], "unset", 5) == 0) // change the argv[1] part (depending on struct)
		builtin_unset();
	else if (ft_strncmp(argv[1], "env", 3) == 0) // change the argv[1] part (depending on struct)
		builtin_env();
	else if (ft_strncmp(argv[1], "exit", 4) == 0) // change the argv[1] part (depending on struct)
		builtin_exit();
		// can't we just use the "real exit" function here, and leave the shell?
}
