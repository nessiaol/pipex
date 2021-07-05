#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>	//per waitpid
# include <fcntl.h>		//per unlink
# define MAXLINE 64

typedef struct s_data
{
	char	**cmd_and_flags;	//comando e tutte le sue flags
	char	*file_1;
	char	*file_2;
	int		fd_file_1;
	int		fd_file_2;
	int		pipe_fd[2];		//p[0] viene usato per il read e p[1] viene usato per il write, i valori all'interno comunicano la fine del processo indicato.
}			t_data;

/*
** Minilibft functions
*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
char	**ft_strsplit(char const *s, char c);
char	*ft_strcat(char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_strdel(char **as);

/*
** Pipex functions
*/
int		ft_index_position(char **src, char *to_find);
int		ft_access(char *path);
void	ft_call_child(char **argv, char **envp, t_data *data);
void	ft_call_father(char **argv, char **envp, t_data *data);

#endif