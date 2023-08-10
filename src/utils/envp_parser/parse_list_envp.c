
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

static void print_envp_list(t_mini_envp_list *mini_envp_list)
{
	while (mini_envp_list != NULL)
	{
		printf("%s\n", mini_envp_list->str);
		mini_envp_list = mini_envp_list->next;
	}
}

static t_mini_envp_list	*find_last_envp(t_mini_envp_list *mini_envp_list)
{
	if (mini_envp_list == NULL)
		return (NULL);
	while (mini_envp_list->next != NULL)
		mini_envp_list = mini_envp_list->next;
	return (mini_envp_list);
}

static void add_envp_node(t_mini_envp_list **envp_list, char *str)
{
	t_mini_envp_list	*new_envp;
	t_mini_envp_list	*last_node;

	last_node = NULL;
	new_envp = malloc(sizeof(t_mini_envp_list));
	if (new_envp == NULL)
		ft_error("Malloc token fail\n");
	new_envp->str = str;
	new_envp->next = NULL;
	if (*envp_list == NULL)
		*envp_list = new_envp;
	else
	{
		last_node = find_last_envp(*envp_list);
		last_node->next = new_envp;
	}
}

void parse_list_envp(t_data *mini_data, char **envp)
{
	int count;

	count = 0;
	while (envp[count] != NULL)
	{
		add_envp_node(&mini_data->mini_envp_list, envp[count]);
		count++;
	}
//	print_envp_list(mini_data->mini_envp_list);
}