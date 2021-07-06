#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>	//per waitpid
# include <fcntl.h>		//per unlink
# define MAXLINE 64

typedef struct s_data
{
	char	**cmd_and_flags;	//comando e tutte le sue flags
	char	*cmd_1;
	char	*cmd_2;
	char	*path_cmd_1;
	char	*path_cmd_2;
	char	*file_1;
	char	*file_2;
	int		fd_file_1;
	int		fd_file_2;
	int		pipe_fd[2];		//p[0] viene usato per il read e p[1] viene usato per il write, i valori all'interno comunicano la fine del processo indicato.
}			t_data;

/*
** Minilibft functions
*/
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char const *s, int fd);
char		**ft_strsplit(char *s, char c);
char		*ft_strcat(char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_strdel(char **as);
void		*ft_memalloc(size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strcpy(char *dst, const char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*
** Pipex functions
*/
// static int	open_file(char  *file_name, char **envp, int flags, int mode);
int		ft_index_position(char **src, char *to_find);
int		ft_access_file(char *path);
void	ft_call_child(char **argv, t_data *data);
void	ft_call_father(char **argv, t_data *data);

void	ft_parse_cmds(t_data *data, char **argv, int argc, char **envp);
int		ft_search_cmd(t_data *data, char **argv, char **envp);

void	ft_free_all(void *arg1, ...);
char	*ft_strtoupper(char *str);
int		ft_toupper(int c);
char	*ft_strnew(size_t size);
int	get_nbwords(char const *s, char c);
char	*ft_strsub(char const *s, unsigned int start, size_t len);

#endif