//
// Created by laura on 26-7-23.
//
#include "../../include/minishell.h"
#include "../../include/cmd_list_actions.h"
#include <stdio.h>

void print_in(t_infile *in)
{
	while(in)
	{
		printf("cmd in: %s   type: %d\n", in->file, in->type);
		in = in->next;
	}
}

void print_out(t_outfile *out)
{
	while(out)
	{
		printf("cmd out: %s    type: %d\n", out->file, out->type);
		out = out->next;
	}
}

void print_cmd_list(t_commands *cmd)
{
	while (cmd)
	{
		printf("cmd: %s\n", cmd->cmd);
		print_in(cmd->infiles);
		print_out(cmd->outfiles);
		cmd = cmd->next;
	}
}