/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:11:06 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 14:48:45 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	builtin_pwd(t_data *mini)
{
	char 	*pwd_path;
	char 	*pwd;
	int 	len;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (ft_exit(errno)); // check this exit tho
	pwd = ft_calloc((ft_strlen(pwd_path) + 2), sizeof(char)); // for null term + newline
	if (pwd == NULL)
		return (ft_exit(errno)); // check this exit tho
	ft_memmove(pwd, pwd_path, ft_strlen(pwd_path));
	len = ft_strlen(pwd);
	pwd[len] = '\n';
	ft_putstr_fd(pwd, mini->commands->out);
	free(pwd_path);
	free(pwd);
	return (0);
}
