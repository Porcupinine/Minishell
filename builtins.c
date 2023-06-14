/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/14 13:02:52 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	builtin_echo(char **argv) // or command (check struct naming)
{
	if (ft_strncmp(argv[1], "echo -n", 7) == 0)
		printf("%s", argv[2]); // without \n at the end
	else
		printf("%s\n", argv[2]); // or whatever
	// for both handle the $ or not ?? think so
	// what do we return? exit code?
}

void	builtin_cd()
{
	// Q: whats a relative or absolute path?
}

void	builtin_pwd(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
			if (ft_strncmp(envp[i], "PWD=", 4) == 0)
				break ;
			i++;
	}
	// check if found somehow
	printf("%s", envp[i] + 4); // is string format right ??
	// return something ??
}

void	builtin_export()
{
	// export a variable
	// do we support the = something ??
}

void	builtin_unset() // unset values and attributes of variables and functions
{
	// via envp (PATH and SHELL)??
	// Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.
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
