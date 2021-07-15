/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:18:36 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/15 15:24:18 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_check_args(t_data *data, char **argv, char **envp)
{
	ft_parse_cmd_1(data, argv, envp);
	ft_parse_cmd_2(data, argv, envp);
	ft_checkfile_1(data, argv, envp);
	ft_checkfile_2(data, argv, envp);
}

void	ft_call_parent(pid_t pid, t_data *data, char **envp)
{
		int	status;

		pid=fork();
		if (pid==0)
		{
			ft_exec_cmd_2(data, envp);
			exit(1);
		}
		else
		{
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			waitpid(pid, &status, 0);
		}
}

void	ft_init(t_data *data)
{
	data->path_cmd_1 = NULL;
	data->path_cmd_2 = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_data	data;

	if (argc == 5)
	{
		ft_init(&data);
		ft_check_args(&data, argv, envp);
		if (pipe(data.pipe_fd) < 0)
		{
			perror("error pipe\n");
			exit(1);
		}
		if ((pid = fork()) < 0)
		{
			perror("error fork\n");
			exit(1);
		}
		if (pid == 0)
		{
			ft_exec_cmd_1(&data, envp);
			exit(1);
		}
		else
			ft_call_parent(pid, &data, envp);
	}
	else
		ft_putstr_fd("Format: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
	free(data.path_cmd_1);
	free(data.path_cmd_2);
	return (0);
}
