/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/13 18:00:29 by dmaessen         ###   ########.fr       */
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

void builtin_echo()
{
	if (ft_strncmp(argv[1], "echo -n", 7) == 0)
		// printf/write without \n at the end
	else
		// printf/write the given sentence
	// for both handle the $ or not ?? think so
	// what do we return? exit code?
}

void builtin_cd()
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

void builtins(char **envp) // still incomplete (envp needed)
{
	if (ft_strncmp(argv[1], "echo", 4) == 0) // change the argv[1] part (depending on struct)
		builtin_echo();
	else if (ft_strncmp(argv[1], "cd", 2) == 0) // change the argv[1] part (depending on struct)
		builtin_cd();
	else if (ft_strncmp(argv[1], "pwd", 3) == 0) // change the argv[1] part (depending on struct)
		builtin_pwd(envp);
	else if (ft_strncmp(argv[1], "export", 6) == 0) // change the argv[1] part (depending on struct)
		builtin_export();
	else if (ft_strncmp(argv[1], "unset", 5) == 0) // change the argv[1] part (depending on struct)
		//
	else if (ft_strncmp(argv[1], "env", 3) == 0) // change the argv[1] part (depending on struct)
		//
	else if (ft_strncmp(argv[1], "exit", 4) == 0) // change the argv[1] part (depending on struct)
		// can't we just use the "real exit" function here, and leave the shell?
}
