/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:18:36 by bde-luca          #+#    #+#             */
/*   Updated: 2021/06/30 18:37:08 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	open_file(char  *file_name, char **envp, int flags, int mode)
{
	int		index_position;
	char	*pwd;
	char	*wd_path;
	char	*file_path;

	index_position = find_index_position(envp, "PWD=");
	pwd = envp[index_position] + 4;
	wd_path = ft_strjoin(pwd, '/');
	file_path = ft_strjoin(wd_path, file_name);
	ft_strdel(&wd_path);
	if ((flags == (O_RDWR | O_CREAT)) || ft_access(file_path))
	{
		if (mode)
			index_position = open (file_path, flags, mode);
		else
			index_position = open(file_path, flags);
		ft_strdel(&file_path);
		return (index_position);
	}
	ft_strdel(&file_path);
	return(-1);
}

void ft_call_father(char **argv, char **envp, t_data *data)
{
	int		n;					//byte letti in read
	char	line[MAXLINE];		//buffer per lettura
	close(data->pipe_fd[1]);	//chiude la scrittura
	n = read(data->pipe_fd[0], line, MAXLINE);		//legge dall'estremo di lettura della pipe
	write(STDOUT_FILENO, line, n);		//scrive in output quello che legge dalla pipe
}

void ft_call_child(char **argv, char **envp, t_data *data)
{
	close(data->pipe_fd[0]);	//chiude la lettura
	write(data->pipe_fd[1], "hello world\n", 12);	//scrive sull'estremo di scrittura della pipe
}

int	main(int argc, char **argv, char **envp)		//aggiungere char **envp quando serve int argc, char **argv
{
	pid_t	pid;
	t_data	*data;

	if (argc == 5)
	{
		ft_divide_cmd(argc, argv, envp, &data);
		if (pipe(&data->pipe_fd) < 0)		//CREA LA PIPE
		{
			perror("pipe");
			exit(1);
		}
		if ((pid = fork()) < 0)		//CREA PARENT/CHILD CON FORK
		{
			perror("fork");
			exit(1);
		}

		printf("argc: %d argv: %s pid: %d\n", argc, argv[1], pid);
		waitpid(0, &data->pipe_fd, 0);	//il primo 0 e' il pid child e il secondo zero e' l'exit del processo indicato (child)
		//si puo' mettere anche wait(NULL) che aspetta che tutti i processi child abbiano exit(0) per eseguire il parent.

		if (pid == 0)
			ft_call_child(argv, envp, &data->pipe_fd);
		else
			ft_call_father(argv, envp, &data->pipe_fd);
	}
	else
		ft_putstr_fd("Format: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
	return (0);
}
