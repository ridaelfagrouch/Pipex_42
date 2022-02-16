/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:48:41 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/16 17:52:00 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//***********************free_split*****************************

void	free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

//*************************found_path***************************

char	*found_path(t_data *data)
{
	while (data->path_split[data->i])
	{
		data->ptr = ft_strjoin(data->path_split[data->i], "/");
		data->final_path = ft_strjoin(data->ptr, data->cmd);
		free(data->ptr);
		data->check_access = access(data->final_path, X_OK | F_OK);
		if (data->check_access == 0)
			break ;
		else
			free(data->final_path);
		data->i++;
	}
	if (data->check_access != 0)
	{
		write(data->dap_out, "error! path not found\n", 23);
		exit(1);
	}
	free_split(data->path_split);
	return (data->final_path);
}

//*************************check_cmd***************************

void	check_cmd(t_data *data, char *av)
{
	if (ft_strchr(av, ' ') != 0)
	{
		data->cmd_split = ft_split(av, ' ');
		if (data->cmd_split[0] == NULL)
		{
			write(data->dap_out, "command not found!\n", 19);
			exit(1);
		}
		data->cmd = ft_strdup(data->cmd_split[0]);
		free_split(data->cmd_split);
	}
	else
		data->cmd = av;
}

//************************get_path****************************

char	*get_path(char **env, char *av, t_data *data)
{
	data->i = 0;
	data->path = NULL;
	data->cmd_split = NULL;
	check_cmd(data, av);
	while (env[data->i])
	{
		if (ft_strnstr(env[data->i], "PATH", 4) != NULL)
		{
			data->path = ft_strtrim(env[data->i], "PATH=");
			break ;
		}
		data->i++;
	}
	if (data->path == NULL)
	{
		write(1, "path not found!\n", 16);
		exit(1);
	}
	data->path_split = ft_split(data->path, ':');
	free(data->path);
	data->i = 0;
	return (found_path(data));
}
