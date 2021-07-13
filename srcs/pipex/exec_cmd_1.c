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
	data->fd_file_1 = open(data->file_1, O_RDONLY);	//apertura file da usare come input
	dup2(data->fd_file_1, 0);						//scambia stdin con FD del file 1
	dup2(data->pipe_fd[1], 1);						//scambia l'output con l'estremo di scrittura della pipe
	if (!(execve(data->path_cmd_1, data->cmd_and_flags, envp)))
	{
		perror("Command 1 not executable\n");
		exit(1);
	}
	//close(data->fd_file_1);				//chiusura file da usare come input
	dup2(0, data->fd_file_1);				//rimette a posto la standard in
	dup2(1, data->pipe_fd[1]);				//rimette a posto lo standard out
	
	// qui dobbiamo mettere dup2 tra 1, 0.
}

void	ft_exec_cmd_2(t_data *data, char **envp)
{
	data->fd_file_2 = open(data->file_2, O_RDWR);	//apertura file da usare come input
	dup2(data->pipe_fd[0], 0);		//scambia standard input con cioò che ha letto dalla pipe
	dup2(data->fd_file_2, 1);		//scambia standard output con f2
	if (!(execve(data->path_cmd_2, data->cmd_and_flags_2, envp)))
	{
		perror("Command 2 not executable\n");
		exit(1);
	}
	close(data->fd_file_2);				//chiusura file da usare come input

	//dup2(1, data->fd_file_2);				//rimette a posto la standard output
	//dup2(0, data->pipe_fd[0]);				//rimette a posto lo standard input
}