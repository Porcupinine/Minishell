/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:11:06 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 14:16:36 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	builtin_pwd(t_data *mini)
{
	char	*pwd_path;
	char	*pwd;
	int		len;

	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (set_exit_code(mini, errno),
			err_msg("getcwd", "failed\n"), -1);
	pwd = ft_calloc_exit((ft_strlen(pwd_path) + 2), sizeof(char));
	ft_memmove(pwd, pwd_path, ft_strlen(pwd_path));
	len = ft_strlen(pwd);
	pwd[len] = '\n';
	ft_putstr_fd(pwd, mini->commands->out);
	free(pwd_path);
	free(pwd);
	return (set_exit_code(mini, 0), 0);
}
