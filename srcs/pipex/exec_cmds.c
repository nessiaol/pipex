/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmangola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:18:33 by dmangola          #+#    #+#             */
/*   Updated: 2021/07/12 17:18:49 by dmangola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_exec_cmd_1(t_data *data, char **envp)
{
	data->fd_file_1 = open(data->file_1, O_RDWR);
	dup2(data->pipe_fd[1], 1);
	dup2(data->fd_file_1, 0);
    close(data->pipe_fd[0]);
    close(data->pipe_fd[1]);
    execve(data->path_cmd_1, data->cmd_and_flags, envp);
	close(data->fd_file_1);
}

void	ft_exec_cmd_2(t_data *data, char **envp)
{
	data->fd_file_1 = open(data->file_1, O_RDWR);
	data->fd_file_2 = open(data->file_2, O_RDWR);
	dup2(data->fd_file_1, 0);
	dup2(data->fd_file_2, 1);
	//dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	printf("path cmd 2: %s", data->path_cmd_2);

	execve(data->path_cmd_2, data->cmd_and_flags_2, envp);
	close(data->fd_file_2);					//chiusura file da usare come input
	close(data->fd_file_1);
	//dup2(1, data->fd_file_2);				//rimette a posto la standard output
	//dup2(0, data->pipe_fd[0]);				//rimette a posto lo standard input
}