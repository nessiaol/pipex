#include "../../includes/pipex.h"

void	ft_parse_cmds(t_data *data, char **argv, int argc, char **envp)
{
	// char **temp;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	printf("argc = %d\n", argc);		//messa per usare argc, se inutile poi lo togliamo dagli argomenti
	if(!(data->cmd_and_flags = ft_strsplit(argv[2], ' ')))
	{
		perror("Split of command/flags not valid\n");
		exit(1);
	}
	data->cmd_and_flags[0] = data->cmd_1;
	if (!ft_search_cmd(data, argv, envp))
	{
		perror("Error: not executable command.\n");
		exit(1);
	}
	//data->cmd_and_flags[1] e eventualmente [2] [3] [4] ecc. = flag del comando
	
}

int	ft_search_cmd(t_data *data, char **argv, char **envp)
{
	short	i;
	char	*path;
	char	**splitted_paths;
	char	*buffer_tmp;
	char	*buffer_path;
	
	i = 0;
	printf("nome programma: %s\n", argv[0]);		//messa per usare argv, se inutile poi lo togliamo dagli argomenti
	path = envp[ft_index_position(envp, "PATH=")] + 5;
	splitted_paths = ft_strsplit(path, ':');
    while (splitted_paths[i])
	{
		buffer_tmp = ft_strjoin(splitted_paths[i], "/");
		buffer_path = ft_strjoin(buffer_tmp, data->cmd_1);
		if (access(buffer_path, X_OK))
		{
			data->path_cmd_1 = buffer_path;
			ft_free_all(splitted_paths, buffer_path, buffer_tmp);
			return(1);
		}
		else
			i++;
	}	
	ft_free_all(splitted_paths, buffer_path, buffer_tmp);
	return(0);
}