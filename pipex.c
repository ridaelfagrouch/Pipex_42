/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:45:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/14 03:24:00 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./pipex_libft/libft.h"
#include <stdio.h>
#include "pipex.h"

// void red () {
//   printf("\033[1;31m");
// }

// void reset () {
//   printf("\033[0m");
// }

// void yellow (){
//   printf("\033[1;33m");
// }


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

char	*get_path(char **env, char *av, t_data *data)
{
	data->i = 0;
	data->path = NULL;
	if (ft_strchr(av, ' ') != 0)
	{
		data->cmd_split = ft_split(av, ' ');
		data->cmd = ft_strdup(data->cmd_split[0]);
		free_split(data->cmd_split);
	}
	else
		data->cmd = av;
	while (env[data->i])
	{
		if (ft_strnstr(env[data->i], "PATH", 4) != NULL)
		{
			data->path = ft_strtrim(env[data->i], "PATH=");
			break ;
		}
		data->i++;
	}
	data->path_split = ft_split(data->path, ':');
	free(data->path);
	data->i = 0;
	while (data->path_split[data->i])
	{
		data->ptr = ft_strjoin(data->path_split[data->i], "/");
		data->final_path = ft_strjoin(data->ptr, data->cmd);
		free(data->ptr);
		data->check_access = access(data->final_path, X_OK);
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

//****************************************************

void	child(int fd[2], char **av, char *env[], t_data *data)
{
	char	**str;

	// if (ft_strncmp(av[2], "ls -lR /", 8) == 0 || \
	// 	ft_strncmp(av[2], "ls -LR /", 8) == 0)
	// {
	// 	write(data->dap_out, "output of cmd to big!\n", 22);
	// 	exite(1);
	// }
	data->pro.path = NULL;
	data->pro.dup_check1 = dup2(fd[1], STDOUT_FILENO);
	data->pro.dup_check2 = dup2(data->pro.file1, STDIN_FILENO);
	if (data->pro.dup_check1 == -1 || data->pro.dup_check2 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(fd[0]);
	data->pro.path = get_path(env, av[2], data);
	str = ft_split(av[2], ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

void	parent(int fd[2], char **av, char *env[], t_data *data)
{
	char	**str;

	// if (ft_strncmp(av[3], "ls -lR /", 8) == 0 || \
	// 	ft_strncmp(av[3], "ls -LR /", 8) == 0)
	// {
	// 	write(data->dap_out, "output of cmd to big!\n", 22);
	// 	exite(1);
	// }
	data->pro.path = NULL;
	data->pro.dup_check1 = dup2(fd[0], STDIN_FILENO);
	data->pro.dup_check2 = dup2(data->pro.file2, STDOUT_FILENO);
	if (data->pro.dup_check1 == -1 || data->pro.dup_check2 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(fd[1]);
	data->pro.path = get_path(env, av[3], data);
	str = ft_split(av[3], ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

void	creat_pipe(char **av, char *env[], t_data *data)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		write(1, "error ocurred with opening the pipe\n", 36);
		exit(1);
	}
	if (access(av[1], F_OK) != 0)
	{
		write(data->dap_out, "filein not exist!\n", 18);
		exit(1);
	}
	if (access(av[1], R_OK) != 0)
		data->pro.file1 = open(av[1], O_RDONLY | 00400);
	if(access(av[4], F_OK) != 0)
		data->pro.file2 = open(av[4], O_CREAT | O_RDWR, 00774);
	
	pid = fork();
	if (pid == -1)
	{
		write(data->dap_out, "error fork\n", 11);
		exit(1);
	}
	if (pid == 0)
		child(fd, av, env, data);
	else
	{
		wait(NULL);
		parent(fd, av, env, data);
	}
}

//****************************************************

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data.dap_out = dup(1);
	if (ac == 5)
		creat_pipe(av, env, &data);
	else
	{
		write(data.dap_out, "error!!", 7);
		exit(1);
	}
	return (0);
}
