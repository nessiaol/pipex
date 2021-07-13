/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:56:04 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/06 19:06:15 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_index_position(char **src, char *to_find)
{
	int	i;

	i = 0;
	to_find = ft_strtoupper(to_find);
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

int	ft_access_file(char *path)
{
	if (access(path, F_OK) == -1)
		ft_putstr_fd("open: no such file or directory\n", 2);
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("open: READ permission denied\n", 2);
	else if (access(path, W_OK) == -1)
		ft_putstr_fd("open: WRITE permission denied\n", 2);
	else
		return (1);
	return (0);
}

// int	open_file(char  *file_name, char **envp, int flags, int mode)
// {
// 	int		index_position;
// 	char	*pwd;
// 	char	*wd_path;
// 	char	*file_path;

// 	index_position = ft_index_position(envp, "PWD=");
// 	pwd = envp[index_position] + 4;
// 	wd_path = ft_strjoin(pwd, "/");
// 	file_path = ft_strjoin(wd_path, file_name);
// 	ft_strdel(&wd_path);
// 	if ((flags == (O_RDWR | O_CREAT)) || ft_access_file(file_path))
// 	{
// 		if (mode)
// 			index_position = open(file_path, flags, mode);
// 		else
// 			index_position = open(file_path, flags);
// 		ft_strdel(&file_path);
// 		return (index_position);
// 	}	
// 	ft_strdel(&file_path);
// 	return(-1);
// }