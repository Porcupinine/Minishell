//
// Created by Laura Praca Lacerda on 8/7/23.
//
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

void print_envp(char ** mini_envp)
{
	int count;

	count = 0;
	while (mini_envp[count] != NULL)
	{
		printf("%s\n", mini_envp[count]);
		count++;
	}
}

static int count_envp(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
	{
		count++;
	}
	return (count);
}

void parse_array_envp(t_data *mini_data, char **envp)
{
	int		count;

	count = 0;
	mini_data->mini_envp = ft_calloc(count_envp(envp) + 1, sizeof (char*));
	if (mini_data->mini_envp == NULL)
		ft_error("Malloc fail\n");
	while (envp[count] != NULL)
	{
		mini_data->mini_envp[count] = ft_strdup(envp[count]);
		count++;
	}
	mini_data->mini_envp[count] = NULL;
	print_envp(mini_data->mini_envp);
}
