/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:18:21 by lpraca-l          #+#    #+#             */
/*   Updated: 2023/09/06 15:10:43 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>

/**
 * @brief Allocates (with malloc(3)) and returns a new
 *string, which is the result of the concatenation
 *of ’s1’ and ’s2’.
 * 
 * @param s1 first string
 * @param s2 second string
 * @return Returns the new string or NULL if the allocation fails. 
 */
char	*ft_strjoin_gnl(char const *s1, char const *s2, long buff_len);

char	*get_next_line_exit(int fd);

/**
 * @brief strlcpy() and strlcat() functions copy and concatenate strings with
 *the same input parameters and output result as snprintf(3).  They are
 *designed to be safer, more consistent, and less error prone replacements
 *for the easily misused functions strncpy(3) and strncat(3).
 *strlcpy() and strlcat() take the full size of the destination buffer and
 *guarantee NUL-termination if there is room.  Note that room for the NUL
 *should be included in dstsize.
 *strlcpy() copies up to dstsize - 1 characters from the string src to dst,
 *NUL-terminating the result if dstsize is not 0.
 *
 * @param src source
 * @param dstsize how much to copy
 * @return the copied string
 */
char	*ft_strlcpy_gnl(const char	*src, long dst_size);

/**
 * @brief The strlen() function calculates the length of the string pointed to 
 *by s, excluding the terminating null byte ('\0').
 * 
 * @param c 
 * @return The strlen() function returns the number of bytes in the string 
 *pointed to by s. 
 */
int		ft_strlen_gnl(const char *c);

void	ft_bzero_gnl(void *s, size_t n);

char	*get_next_line_fd(int fd);
void	ft_free_b(char **memory, char *line);
char	*ft_strjoin_gnl_b(char *memory, char *buf);
char	*ft_strchr_gnl_b(const char *s, int c);
void	*ft_calloc_b(size_t count, size_t size);
char	*ft_substr_gnl_b(char const *s, unsigned int start, size_t len);

#endif