/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:19:38 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 15:48:37 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	array_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size] != NULL)
		size++;
	return (size);
}

int	lst_size(t_commands *lst)
{
	int			count;
	t_commands	*position;

	count = 0;
	position = lst;
	while (position != NULL)
	{
		position = position->next;
		count++;
	}
	return (count);
}

void	pid_lstadd_back(t_pid **lst, pid_t content)
{
	t_pid	*last_node;
	t_pid	*new_node;

	new_node = ft_calloc_exit(1, sizeof(t_pid));
	new_node->pid = content;
	new_node->next = NULL;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		last_node = pid_lstlast(*lst);
		last_node->next = new_node;
	}
}

t_pid	*pid_lstlast(t_pid *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
