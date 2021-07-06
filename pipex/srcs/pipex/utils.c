/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:56:04 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/05 19:25:29 by bde-luca         ###   ########.fr       */
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
		ft_putstr_fd("open: no such file or directory", 2);
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("open: READ permission denied", 2);
	else if (access(path, W_OK) == -1)
		ft_putstr_fd("open: WRITE permission denied", 2);
	else
		return (1);
	return (0);
}

void	ft_free_all(void *arg1, ...)
{
	va_list	args;
	void	*vp;

	free(arg1);
	va_start(args, arg1);
	vp = va_arg(args, void *);
	while (vp != 0)
		free(vp);
	va_end(args);
}
