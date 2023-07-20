/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 19:47:08 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/05/23 15:14:27 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/**
 * Erases the data in the n bytes of the memory starting
 * at the location pointed to by s, by writing zeros (bytes containing '\0')
 * to that area.
 * @param s location
 * @param n amount of \0
 */
void	ft_bzero(void *s, size_t n);
/**
 * Checks if parameter is alphanumeric
 * @param c what to check
 * @return 0 if it's not or something alse if it is
 */
int		ft_isalnum(int c);
/**
 * Checks if parameter is a character
 * @param c what to check
 * @return 0 if it's not or something else if it is
 */
int		ft_isalpha(int c);
/**
 * Check if parameter is ascii
 * @param c what to check
 * @return 0 if it's not or something else if it is
 */
int		ft_isascii(int c);
/**
 * Check if parameter is a digit
 * @param c what to check
 * @return 0 if it's not or something else if it is
 */
int		ft_isdigit(int c);
/**
 * Checks if it's a printable char
 * @param c what to check
 * @return 0 if it's not or other numbe if it is
 */
int		ft_isprint(int c);
/**
 * The memcpy() function copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap.  Use memmove(3) if the memory areas do
 * overlap.
 * @param dest dest mem area
 * @param src src mem area
 * @param n how much to copy
 * @return pointer to dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);
/**
 * The memmove() function copies n bytes from memory area src to
 * memory area dest.The memory areas may overlap:copying takes place as though
 * the bytes in src are first copied into a temporary array that does  not 
 * overlap src or dest, and the bytes are then copied from the temporary 
 * array to dest.
 * @param dest dest mem area
 * @param src src mem area
 * @param n how much to copy
 * @return a pointer to dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n);
/**
 * The memset() function fills the first n bytes of the memory area pointed to
 * by s with the constant byte c.
 * @param s mem to be filled
 * @param c constant to fill
 * @param n how much to fill
 * @return pointer to s
 */
void	*ft_memset(void *s, int c, size_t n);
/**
 * Gets the length
 * @param c string to be mesured
 * @return length of the string
 */
size_t	ft_strlen(const char *c);
/**
 * Copies up to dstsize - 1 characters from the string src to dst,
 * NUL-terminating the result if dstsize is not 0.
 * @param dst dst string
 * @param src src string
 * @param dstsize how much to copy
 * @return return the length of the string the function tried to create
 */
size_t	ft_strlcpy(char	*dst, const char	*src, size_t dstsize);
/**
 * Make char upper case
 * @param c char
 * @return upper case char
 */
int		ft_toupper(int c);
/**
 * Make char lower case
 * @param c char
 * @return lower case char
 */
int		ft_tolower(int c);
/**
 * Finds first occurrence of a char c in a string s
 * @param s string
 * @param c what to find
 * @return pointer to the char or 0 if nothing is found
 */
char	*ft_strchr(const char *s, int c);
/**
 * Finds last occurrence of a char in a string s
 * @param s string
 * @param c what to find
 * @return pointer to tge char or 0 if nothing is found
 */
char	*ft_strrchr(const char *s, int c);
/**
 * Compare n bytes from two strings
 * @param s1 string 1
 * @param s2 string 2
 * @param n how much toc compare
 * @return return an integer greater than,
 *  equal to, or less than 0, according as the string s1 is greater than,
 * equal to, or less than the string s2
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * Compare n bytes of mem1 and men2
 * @param s1 "string"1
 * @param s2 "string"2
 * @param n how much to compare
 * @return 0 if identical or the difference between
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * Loooks for needle on a haystack not more than n bytes
 * @param haystack
 * @param needle
 * @param len how much to look
 * @return pointer to needle or 0
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/**
 * Appends string src to the end of dst. It will append at most
 * dstsize - strlen(dst) - 1 characters and NULL terminates it
 * @param dst dst string
 * @param src src string
 * @param dstsize how much to append
 * @return the length of the string it tried to create
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/**
 * Convert a char to an int
 * @param nptr string
 * @return integer
 */
int		ft_atoi(const char *nptr);
/**
 * Duplicates a string
 * @param s1 string to be duplicated
 * @return duplicated string
 */
char	*ft_strdup(const char *s1);
/**
 * Contiguously allocates enough space for count
 * objects that are size bytes of memory each and returns a pointer to the
 * allocated memory.  The allocated memory is filled with bytes of value
 * zero.
 * @param count how much
 * @param size type
 * @return NULL if it fails
 */
void	*ft_calloc(size_t count, size_t size);
/**
 * Allocates (with malloc(3)) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is ofmaximum size ’len’.
 * @param s src string
 * @param start pointer to the star of the new string insed src
 * @param len how long the new string willl be
 * @return new string or NULL if it fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation
 * of ’s1’ and ’s2’.
 * @param s1 string 1
 * @param s2 string 2
 * @return resulting string or NULL if it fails
 */
char	*ft_strjoin(char const *s1, char const *s2);
/**
 * Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 * @param s1 string
 * @param set what to cut
 * @return trimed string or NULL if fails
 */
char	*ft_strtrim(char const *s1, char const *set);
/**
 * Writes string s on chosen file descriptor fd
 * @param s string
 * @param fd file descriptor
 */
void	ft_putstr_fd(char *s, int fd);
/**
 * Writes char c on chose file descriptor fd
 * @param c char
 * @param fd file descriptor
 */
void	ft_putchar_fd(char c, int fd);
/**
 * Writes string s on chosen file descriptor fd followed by new line
 * @param s string
 * @param fd file descriptor
 */
void	ft_putendl_fd(char *s, int fd);
/**
 * Writes a integer n on chosen file descriptor fd
 * @param n integer
 * @param fd file descriptor
 */
void	ft_putnbr_fd(int n, int fd);
/**
 * Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter. The array must end
 * with a NULL pointer.
 * @param s string
 * @param c separator
 * @return array of strings or NULL if fails
 */
char	**ft_split(char const *s, char c);
/**
 * Converts integer to char
 * @param n number
 * @return string
 */
char	*ft_itoa(int n);
/**
 * Applies the function ’f’ to each character of the
 * string ’s’, and passing its index as first argument
 * to create a new string (with malloc(3)) resulting
 * from successive applications of ’f’.
 * @param s string
 * @param f function
 * @return string created from the successive applications
 * of ’f’or NULL if fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * Applies the function ’f’ on each character of
 * the string passed as argument, passing its index
 * as first argument. Each character is passed by
 * address to ’f’ to be modified if necessary
 * @param s string
 * @param f function
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/**
 * Allocates (with malloc(3)) and returns a new node.
 * The member variable ’content’ is initialized with
 * the value of the parameter ’content’. The variable
 * ’next’ is initialized to NULL.
 * @param content content of the new node
 * @return new node
 */
t_list	*ft_lstnew(void *content);
/**
 * Adds the node ’new’ at the beginning of the list.
 * @param lst list head
 * @param new_node new node
 */
void	ft_lstadd_front(t_list **lst, t_list *new_node);
/**
 * get size of the list
 * @param lst list head
 * @return list size
 */
int		ft_lstsize(t_list *lst);
/**
 * finds the last node of a list
 * @param lst list head
 * @return last node
 */
t_list	*ft_lstlast(t_list *lst);
/**
 *  * Adds the node ’new’ at the end of the list.
 * @param lst list head
 * @param new_node new node
 */
void	ft_lstadd_back(t_list **lst, t_list *new_node);
/**
 * Takes as a parameter a node and frees the memory of
 * the node’s content using the function ’del’ given
 * as a parameter and free the node. The memory of
 * ’next’ must not be freed.
 * @param lst list
 * @param del del function
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));
/**
 * Deletes and frees the given node and every
 * successor of that node, using the function ’del’
 * and free(3).
 * @param lst node
 * @param del del function
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));
/**
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node
 * @param lst list head
 * @param f function
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node. Creates a new
 * list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to
 * delete the content of a node if needed.
 * @param lst list head
 * @param f funtion
 * @param del del function
 * @return new list or NULL if fails
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/**
 * locates the first occurrence of c (converted to an
 * unsigned char) in string s.
 * @param s "string"
 * @param c "char"
 * @param n how long
 * @return pointer do char or 0 if nothing is found
 */
void	*ft_memchr(const void *s, int c, size_t n);
/**
 * prints error message and quits
 * @param error
 */
void	ft_error(char *error);
/**
 * Appends a new char to a string
 * @param s1 string
 * @param c char to add
 * @return new string
 */
char	*append_char(char const *s1, char const c);
#endif
