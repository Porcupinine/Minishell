// ADD 42 HEADER

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

static int	ft_atoi_long(char *str)
{
	int		i;
	int		sign;
	long	nb;

	nb = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] >= 48 && str[i] <= 57))
			nb = (nb * 10) + (str[i] - 48);
		else
			return (-1);
		if (nb > INT_MAX || (nb * -1) < INT_MIN) 
			return (-1);
		i++;
	}
	return ((int)(sign * nb));
}

void	builtin_exit(t_data *mini, char *cmd)
{
	int i;
	int j;
	char *sub;
	long long code;

	i = 0;
	while(cmd[i])
		i++;
	if (i == 4 && ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		ft_putstr("exit\n", 2); 
		// and exit with 0 (right??) but things need to be freed first
	i = 0;
	j = 0;
	while(cmd[i])
	{
		if (cmd[i] == " ")
			j++;
		i++;
	}
	if (j > 1) // so more than one arg
	{
		builtin_err("exit", "too many arguments\n");
		// exit with 1 BUT things to free first
	}
	else
	{
		sub = ft_substr(cmd, 5, ft_strlen(cmd));
		code = ft_atoi_long(sub);
		if (code == -1)
		{
			builtin_err("exit", "numeric argument required\n");
			// exit with 255 BUT things to free first
		}
		free(sub); // needed??
	}
	// do we also maybe need to use rl_clear_history ??
	// or something else??
	exit(code); // i doubt its only this.. cannot exit with more than 256 right?? ++ things to be freed
}