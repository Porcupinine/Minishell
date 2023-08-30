//
// Created by Laura Praca Lacerda on 8/30/23.
//

#include "../../Lib42/include/libft.h"

char	*remove_quotes(char *str)
{
	char *tmp;
	int count_quotes;
	int count;
	int count_tmp;

	count_tmp = 0;
	count = 0;
	count_quotes = 0;
	while(str[count] != '\0')
	{
		if (str[count] == '\'' || str[count] == '"')
			count_quotes++;
		count++;
	}
	count = 0;
	tmp = ft_calloc_exit(((ft_strlen(str) - count_quotes) + 1), sizeof (char));
	while (str[count] != '\0')
	{
		if (str[count] != '\'' && str[count] != '"')
		{
			tmp[count_tmp] = str[count];
			count_tmp++;
		}
		count++;
	}
	return(str);
}