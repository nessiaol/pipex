/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:18:36 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/14 14:13:37 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_data	data;

	if (argc == 5)
	{
		ft_parse_cmd_1(&data, argv, envp);
		ft_parse_cmd_2(&data, argv, envp);
		ft_checkfile_1(&data, argv, envp);
		ft_checkfile_2(&data, argv, envp);
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
		if (pid == 0)
		{
			ft_exec_cmd_1(&data, envp);
			exit(1);
		}
		else
		{ 
			pid=fork();

			if (pid==0)
			{
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
	check_leaks();
	return (0);
}
