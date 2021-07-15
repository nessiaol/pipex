#include "../../includes/pipex.h"

void	ft_parse_cmd_2(t_data *data, char **argv, char **envp)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if(!(data->cmd_and_flags_2 = ft_strsplit(argv[3], ' ')))
	{
		perror("Split of command/flags not valid\n");
		exit(1);
	}
	data->cmd_2 = data->cmd_and_flags_2[0];
	if (!ft_search_cmd_2(data, envp))
	{
		perror("Error: not executable command.\n");
		exit(1);
	}	
}

int	ft_search_cmd_2(t_data *data, char **envp)
{
	short	i;
	short	x;
	char	*path;
	char	**splitted_paths;
	char	*buffer_tmp;
	char	*buffer_path;
	
	i = 0;
	x = 0;
	buffer_path = NULL;
	path = envp[ft_index_position(envp, "PATH=")] + 5;
	splitted_paths = ft_split(path, ':');
    while (splitted_paths[i])
	{
		buffer_tmp = ft_strjoin(splitted_paths[i], "/");
		if (buffer_path)
			free(buffer_path);
		buffer_path = ft_strjoin(buffer_tmp, data->cmd_2);
		free(buffer_tmp);
		if (access(buffer_path, X_OK) != - 1)
		{
			data->path_cmd_2 = strdup(buffer_path);
			while (splitted_paths[x])
			{
				free(splitted_paths[x]);
				x++;
			}
			free(splitted_paths);
			free(buffer_path);
			return(1);
		}
		i++;
	}
	free(buffer_path);
	while (splitted_paths[x])
	{
		free(splitted_paths[x]);
		x++;
	}
	free(splitted_paths);
	return(0);
}