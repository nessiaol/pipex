#include "../../includes/pipex.h"

void	ft_checkfile_1(t_data *data, char **argv, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->file_1 = argv[1];
	if (!ft_search_file_1(data, envp))
	{
		perror("Error: invalid input file.\n");
		exit(1);
	}
}

int	ft_search_file_1(t_data *data, char **envp)
{
	short	i;
	char	*path;
	char	*buffer_tmp;
	char	*buffer_path;

	i = 0;
	path = envp[ft_index_position(envp, "PWD=")] + 4;
	buffer_tmp = ft_strjoin(path, "/");
	buffer_path = ft_strjoin(buffer_tmp, data->file_1);
	free(buffer_tmp);
	if (ft_access_file(buffer_path) > 0)
		return (1);
	free(buffer_path);
	return (0);
}

void	ft_checkfile_2(t_data *data, char **argv, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->file_2 = argv[4];
	if (!ft_search_file_2(data, envp))
	{
		perror("Error: invalid output file.\n");
		exit(1);
	}
}

int	ft_search_file_2(t_data *data, char **envp)
{
	short	i;
	char	*path;
	char	*buffer_tmp;
	char	*buffer_path;

	i = 0;
	path = envp[ft_index_position(envp, "PWD=")] + 4;
	buffer_tmp = ft_strjoin(path, "/");
	buffer_path = ft_strjoin(buffer_tmp, data->file_2);
	free(buffer_tmp);
	if (ft_access_file(buffer_path) > 0)
		return (1);
	free(buffer_path);
	return (0);
}
