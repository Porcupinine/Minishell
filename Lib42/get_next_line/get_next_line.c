/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 19:17:01 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/07/20 11:42:18 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Write a function that returns a line read from a file descriptor
 Repeated calls (e.g., using a loop) to your get_next_line() function should 
let you read the text file pointed to by the file descriptor, one line at a 
time.
• Your function should return the line that was read.
If there is nothing else to read or if an error occurred, it should return NULL.
• Make sure that your function works as expected both when reading a file and 
whenreading from the standard input.
• Please note that the returned line should include the terminating \n 
character, except if the end of file was reached and does not end with a \n 
character.
• Your header file get_next_line.h must at least contain the prototype of the
get_next_line() function.
• Add all the helper functions you need in the get_next_line_utils.c file.
• Because you will have to read files in get_next_line(), add this option to 
your compiler call: -D BUFFER_SIZE=n
It will define the buffer size for read().
The buffer size value will be modified by your peer-evaluators and the 
Moulinette in order to test your code.
• You will compile your code as follows (a buffer size of 42 is used as an 
example): cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
• We consider that get_next_line() has an undefined behavior if the file 
pointed to by the file descriptor changed since the last call whereas read() 
didn’t reach theend of file.
• We also consider that get_next_line() has an undefined behavior when reading
a binary file. However, you can implement a logical way to handle this 
behavior if you want to.
*/

#include <unistd.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

/***
 *
 * @param buff What was last read from fd
 * @param lines Where the function stores the line
 * @param buff_len Size of the buff
 * @param len Which interation we are inside the buff
 * @return 0 if it fails, 3 if it doesn't find a new line or null
 * terminator and 2 if it finds the new line or null terminator
 */
static int	get_line(char *buff, char **lines, long buff_len, long *len)
{
	int		start;
	char	*temp;
	int		line_size;

	start = *len;
	while (*len < (buff_len) && buff[*len] != '\n' && buff[*len] != '\0')
		(*len)++;
	line_size = *len - start;
	if (*lines == NULL)
	{
		if (*len == buff_len)
			(*lines) = ft_strlcpy(buff + start, line_size);
		else if (buff[*len] == '\n' || buff[*len] == '\0')
		{
			if (buff[*len] == '\n')
				line_size++;
			(*lines) = ft_strlcpy(buff + start, line_size);
			(*len)++;
			return (2);
		}
	}
	else
	{
		temp = *lines;
		if (*len == buff_len )
		{
			(*lines) = ft_strjoin((*lines), &(buff[start]), line_size);
			free(temp);
		}
		else if (buff[*len] == '\n' || buff[*len] == '\0')
		{
			if (buff[*len] == '\n')
				line_size++;
			(*lines) = ft_strjoin((*lines), &(buff[start]), line_size);
			(*len)++;
			free(temp);
			return (2);
		}
	}
	return (3);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE];
	char			*lines;
	static long		len = 0;
	static long		buff_len = 0;
	long				ret;

	lines = NULL;
	ret = 0;
	while (1)
	{
		if (len >= buff_len)
		{
			ft_memset(buff, 0, BUFFER_SIZE);
			buff_len = read(fd, buff, BUFFER_SIZE);
			if (buff_len == 0)
				return (lines);
			if (buff_len < 0)
			{
				ft_memset(buff, 0, BUFFER_SIZE);
				free(lines);
				return (NULL);
			}
			len = 0;
		}
		if (buff_len > 0)
			ret = get_line(buff, &lines, buff_len, &len);
		if (ret == 2)
			break ;
	}
	return (lines);
}
