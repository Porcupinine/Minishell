
#include <readline/history.h>
#include <stdlib.h>
#include "../../include/minishell.h"

void line_history(t_data *mini_data)
{
	if (mini_data->command_line == NULL)
		exit(0);
	if(mini_data->command_line)
		add_history(mini_data->command_line);

}