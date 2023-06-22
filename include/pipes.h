#ifndef PIPES_H
# define PIPES_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_pipexb
{
	int		argc;
	char	**argv;
	char	**envp;
	int		in_file;
	int		out_f;
	int		status;
	int		**fd;
	int		index;
}	t_pipexb;

// int		main(int argc, char *argv[], char *envp[]);

void	free_str(char **str);
void	cmd_err(char *argv, int error);
void	no_perm_err(int argc, char *argv[]);
void	cmd_not_found(char **command);

char	*split_args(char *argv, char **envp);

char	**split_command(char *argv);

char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);

void	read_stdin(t_pipexb pipex);
int		ft_heredoc(int argc, char *argv[], char *envp[]);

void	child1(t_pipexb pipex, int fd[]);
void	child2(t_pipexb pipex, int fd[]);

void	which_child(t_pipexb pipex, int i, int pos);

void	close_pipe(int **fd, int argc);

void	free_fd(int **fd, int argc);

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *memory, char *buf);
char	*ft_strchr_gnl(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
void	ft_free(char **memory, char *line);

#endif