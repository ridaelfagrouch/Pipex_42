/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:45:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/10 21:10:58 by rel-fagr         ###   ########.fr       */
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

char	*execv_fan(char **env, char *av)
{
	char	**path_split;
	char	*path;
	char	**cmd_split;
	char	*cmd;
	char	*final_path;
	int		i;
	char	*ptr;

	i = 0;
	if (ft_strchr(av, ' ') != 0)
	{
		cmd_split = ft_split(av, ' ');
		cmd = cmd_split[0];
	}
	else
		cmd = av;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
		{
			path = ft_strdup(&env[i][5]);
			break ;
		}
		i++;
	}
	path_split = ft_split(path, ':');
	i = 0;
	while (path_split[i])
	{
		ptr = ft_strjoin(path_split[i], "/");
		final_path = ft_strjoin(ptr, cmd);
		free(ptr);
		if (access(final_path, F_OK) == 0)
			break ;
		else
			free(final_path);
	}
	return (final_path);
}

//****************************************************

void	child(int fd[2], char **av, char *env[])
{
	int		dup_check1;
	int		dup_check2;
	int		cmd_find;
	int		file1;
	char	*path;

	file1 = open(av[1], O_CREAT, 0666);
	dup_check1 = dup2(fd[1], STDOUT_FILENO);
	dup_check2 = dup2(file1, STDIN_FILENO);
	if (dup_check1 == -1 || dup_check2 == -1)
	{
		write(1, "error dup2\n", 11);
		exit(1);
	}
	close(fd[0]);
	cmd_find = access(av[2], F_OK);
	if (cmd_find != 0)
	{
		write(1, "command does not exist\n", 23);
		exit(1);
	}
	path = execv_fan(env, av[2]);
	execve(path, (char *const *)av[2], env);
}

//****************************************************

void	parent(int fd[2], char **av, char *env[])
{
	int		dup_check1;
	int		dup_check2;
	int		cmd_find;
	int		file2;
	char	*path;

	file2 = open(av[4], O_CREAT, 0666);
	dup_check1 = dup2(fd[0], STDIN_FILENO);
	dup_check2 = dup2(file2, STDOUT_FILENO);
	if (dup_check1 == -1 || dup_check2 == -1)
	{
		write(1, "error dup2\n", 11);
		exit(1);
	}
	close(fd[1]);
	cmd_find = access(av[3], F_OK);
	if (cmd_find != 0)
	{
		write(1, "command does not exist\n", 23);
		exit(1);
	}
	path = execv_fan(env, av[3]);
	execve(path, (char *const *)av[3], env);
}

//****************************************************

void	creat_pipe(int fd[2], int pid, char **av, char *env[])
{
	if (pipe(fd) == -1)
	{
		write(1, "error ocurred with opening the pipe\n", 36);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		write(1, "error fork\n", 11);
		exit(1);
	}
	if (pid == 0)
		child(fd, av, env);
	else
	{
		wait(NULL);
		parent(fd, av, env);
	}
}

//****************************************************

int	main(int ac, char *av[], char *env[])
{
	int		fd[2];
	int		pid;

	pid = 0;
	if (ac == 5)
		creat_pipe(fd, pid, av, env);
	else
	{
		write(1, "error!!", 7);
		exit(1);
	}
	return (0);
}
