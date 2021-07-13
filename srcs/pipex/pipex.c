/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:18:36 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/06 19:35:21 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void ft_call_father(t_data *data, char **envp)
{
	//int		n;					//byte letti in read
	//char	line[MAXLINE];			//buffer per lettura

	
	data->fd_file_2 = open(data->file_2, O_RDWR);	//apertura file da usare come output
	//n = read(data->pipe_fd[0], line, MAXLINE);		//legge dall'estremo di lettura della pipe
	//printf("buffer read: %s\n", data->buffer_read);
	dup2(data->pipe_fd[0], 0);		//scambia standard input con estremo di lettura della pipe
	close(data->pipe_fd[1]);	//chiude la scrittura
	close(data->pipe_fd[0]);	//chiude la lettura
	dup2(data->fd_file_2, 1);		//scambia standard output con f2
	//printf("prova scrittura su f2\n");
	if (!(execve(data->path_cmd_2, data->cmd_and_flags_2, envp)))
	{
		perror("Command 2 not executable\n");
		exit(1);
	}
	close(data->fd_file_2);				//chiusura file da usare come output

	//write(STDOUT_FILENO, data->buffer_read, n);		//scrive in output quello che legge dalla pipe
	//ft_exec_cmd_2(data, envp);
}

void ft_call_child(t_data *data, char **envp)
{
	//close(data->pipe_fd[0]);						//chiude la lettura
	data->fd_file_1 = open(data->file_1, O_RDONLY);	//apertura file da usare come input
	//data->fd_file_2 = open(data->file_2, O_RDWR);	//apertura file da usare come output
	dup2(data->fd_file_1, 0);						//INPUT - scambia stdin con FD del file 1
	close(data->pipe_fd[1]);	//chiude la scrittura
	close(data->pipe_fd[0]);	//chiude la lettura
	//dup2(data->fd_file_2, 1);
	//dup2(data->pipe_fd[1], 1);						//OUTPUT - scambia l'output con l'estremo di scrittura della pipe
	//printf("prova scrittura su pipe\n");
	if (!(execve(data->path_cmd_1, data->cmd_and_flags, envp)))
	{
		perror("Command 1 not executable\n");
		exit(1);
	}
	//close(data->fd_file_1);				//chiusura file da usare come input
	dup2(0, data->fd_file_1);				//rimette a posto la standard in
	//dup2(1, data->pipe_fd[1]);				//rimette a posto lo standard out
	
	//printf("provaaa");
	//ft_exec_cmd_1(data, envp);	//scrive sull'estremo di scrittura della pipe
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_data	data;

	if (argc == 5)
	{
		ft_parse_cmd_1(&data, argv, envp);
		ft_parse_cmd_2(&data, argv, envp);
		//printf("1 path cmd 1: %s\n", data.path_cmd_1);
		//printf("1 path cmd 2: %s\n", data.path_cmd_2);
		//		------------qui cambia la path dei comandi!
		ft_checkfile_1(&data, argv, envp);
		//printf("2 path cmd 1: %s\n", data.path_cmd_1);
		//printf("2 path cmd 2: %s\n", data.path_cmd_2);
		ft_checkfile_2(&data, argv, envp);
		//printf("prova prima di pipe\n");
		//printf("3 path cmd 1: %s\n", data.path_cmd_1);
		//printf("3 path cmd 2: %s\n", data.path_cmd_2);

		if (pipe(data.pipe_fd) < 0)		//CREA LA PIPE
		{
			perror("pipe\n");
			exit(1);
		}
		if ((pid = fork()) < 0)		//CREA PARENT/CHILD CON FORK
		{
			perror("fork\n");
			exit(1);
		}
		//wait(NULL);	//il primo 0 e' il pid child e il secondo zero e' l'exit del processo indicato (child)
		//si puo' mettere anche wait(NULL) che aspetta che tutti i processi child abbiano exit(0) per eseguire il parent.

		if (pid == 0)
		{
			//ft_call_child(&data, envp);
			//ft_exec_cmd_1(&data, envp);
			//printf("prova nel child\n");
			exit(1);
		}
		else
		{ 
			pid=fork();

			if (pid==0)
			{
				//printf("prova nel father\n");
				ft_exec_cmd_2(&data, envp);
				exit(1);
			}
			else
			{
				int status;
				close(data.pipe_fd[0]);
				close(data.pipe_fd[1]);
				waitpid(pid, &status, 0);
			}
		}
	}
	else
		ft_putstr_fd("Format: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
	return (0);
}
