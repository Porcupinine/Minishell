/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 13:59:41 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/31 18:24:52 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
The array of new strings resulting from the split.
NULL if the allocation fails.*/

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		count;
	int		count_words;

	count = 0;
	count_words = 0;
	while (s[count] == c && s[count] != '\0')
			count++;
	while (s[count] != '\0')
	{
		while (s[count] != c && s[count] != '\0')
			count++;
		count_words++;
		while (s[count] == c && s[count] != '\0')
			count++;
	}
	return (count_words);
}

static char	*get_string(char *s, char c, int *count_str)
{
	int		count;
	char	*str;

	while (s[*count_str] == c)
		(*count_str)++;
	count = *count_str;
	while (s[*count_str] != c && s[*count_str] != '\0')
	{
		(*count_str)++;
	}
	str = ft_substr(s, count, (*count_str - count));
	return (str);
}

static int	string_malloc_fail(char **arr, int count_arr)
{
	if (arr[count_arr] == NULL)
	{
		while (count_arr >= 0)
		{
			free(arr[count_arr]);
			count_arr--;
		}
		free(arr);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**arr;
	int		count_str;
	int		count_arr;

	count_str = 0;
	count_arr = 0;
	words = count_words(s, c);
	arr = ft_calloc((words + 1), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (count_arr < words)
	{
		arr[count_arr] = get_string((char *)s, c, &count_str);
		if (string_malloc_fail(arr, count_arr) == 0)
			return (NULL);
		count_arr++;
	}
	arr[count_arr] = NULL;
	return (arr);
}
