//
// Created by laura on 20-7-23.
//
#include "../../../include/lexical_analyzer.h"

int find_size(t_tokens *tokens)
{
	int count;

	count = 0;
	while(tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return(count);
}