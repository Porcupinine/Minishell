/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:11:06 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/27 13:16:36 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
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

void	builtin_pwd(t_data *mini_data)
{
	char *pwd_path;

	pwd_path = malloc((PATH_MAX + 1) * sizeof(char));
	if (pwd_path == NULL)
		return (ft_exit(errno)); // check this exit tho
	if (getcwd(pwd_path, PATH_MAX + 1) == NULL)
		return (ft_exit(errno)); // check this exit tho
	printf("%s", pwd_path);
	free(pwd_path);
	return (0);
}
