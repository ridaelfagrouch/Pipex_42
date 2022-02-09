/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:45:01 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/09 16:09:47 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include <stdio.h>

void	execv_fan(char **env, char *av, int *fd)
{
	char *path_env;
	char **path;
	
	//path_env = ft_strdup(getenv("PATH"));
	path = ft_split(path_env, ':');
	while (*env)
		printf("%s\n", *env++);
}

int	main(int ac, char *av[], char *env[])
{
	int		fd[2];
	int		pid;
	int		cmd_find;
	int		dup_check;
	char	*str;

	fd[0] = open(av[1], O_CREAT | O_RDWR);
	fd[1] = open(av[4], O_CREAT | O_RDWR);
	if (fd[0] < 0 || fd[1] < 0)
		return (-1);
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
	{
		dup_check = dup2(fd[1], STDOUT_FILENO);
		if (dup_check == -1)
		{
			write(1, "error dup2\n", 11);
			exit(1);
		}
		close(fd[0]);
		cmd_find = access(av[2], X_OK | R_OK | F_OK);
		if (cmd_find == -1)
		{
			write(1, "command does not exist\n", 23);
			exit(1);
		}
		execv_fan(env, av[2], &fd[1]);
	}
	else
	{
		wait(NULL);
		dup_check = dup2(fd[0], STDIN_FILENO);
		if (dup_check == -1)
		{
			write(1, "error dup2\n", 11);
			exit(1);
		}
		close(fd[1]);
		cmd_find = access(av[3], X_OK | R_OK | F_OK);
		if (cmd_find == -1)
		{
			write(1, "command does not exist\n", 23);
			exit(1);
		}
		execv_fan(env, av[2], &fd[1]);
	}
	// // close(fd[1]);
	// // close(fd[0]);
	return(0);
}
