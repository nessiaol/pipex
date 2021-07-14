/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:18:33 by dmangola          #+#    #+#             */
/*   Updated: 2021/07/14 14:03:12 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_exec_cmd_1(t_data *data, char **envp)
{
	data->fd_file_1 = open(data->file_1, O_RDWR);
	dup2(data->fd_file_1, 0);		//input
	dup2(data->pipe_fd[1], 1);		//output
    close(data->pipe_fd[0]);
    close(data->pipe_fd[1]);
    execve(data->path_cmd_1, data->cmd_and_flags, envp);
	close(data->fd_file_1);
}

void	ft_exec_cmd_2(t_data *data, char **envp)
{
	data->fd_file_2 = open(data->file_2, O_RDWR);
	dup2(data->pipe_fd[0], 0);			//input
	dup2(data->fd_file_2, 1);			//output
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	execve(data->path_cmd_2, data->cmd_and_flags_2, envp);
	close(data->fd_file_2);					//chiusura file da usare come input
	close(data->fd_file_1);
}