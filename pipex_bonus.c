/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:47:57 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/18 18:49:58 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child(int fd[2], char *av, char *env[], t_data *data)
{
	char	**str;

	data->pro.path = NULL;
	data->pro.dup_check1 = dup2(fd[1], STDOUT_FILENO);
	if (data->pro.dup_check1 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(fd[0]);
	data->pro.path = get_path(env, av, data);
	str = ft_split(av, ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

static void	parent(int fd[2], t_data *data)
{
	data->pro.dup_check1 = dup2(fd[0], STDIN_FILENO);
	if (data->pro.dup_check1 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(fd[1]);
	wait(NULL);
}

//****************************************************

static void	check_file_access(t_data *data, char **av)
{
	if (access(av[1], F_OK) != 0)
	{
		write(data->dap_out, "filein not exist!\n", 18);
		exit(1);
	}
	if (access(av[1], R_OK) != 0)
	{
		write(data->dap_out, "error ocurred with opening the filein!\n", 39);
		exit(1);
	}
	if (access(av[1], R_OK | F_OK) == 0)
		data->pro.file1 = open(av[1], O_RDONLY, 00500);
	if (access(av[data->ac - 1], F_OK) != 0)
	{
		data->pro.file2 = open(av[data->ac - 1], O_CREAT | O_RDWR, 00774);
		if (data->pro.file2 < 0)
		{
			write(data->dap_out, "error! opening the fileout\n", 27);
			exit(1);
		}
	}
	else
		data->pro.file2 = open(av[data->ac - 1], O_RDWR | O_TRUNC, 00774);
}

//****************************************************

static void	creat_pipe(char *av, char *env[], t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		write(1, "error ocurred with opening the pipe\n", 36);
		exit(1);
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		write(data->dap_out, "error fork\n", 11);
		exit(1);
	}
	if (data->pid == 0)
		child(fd, av, env, data);
	else
		parent(fd, data);
}

//****************************************************

static void	dup_file(t_data *data)
{
	data->pro.dup_check2 = dup2(data->pro.file1, STDIN_FILENO);
	if (data->pro.dup_check2 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	data->pro.dup_check3 = dup2(data->pro.file2, STDOUT_FILENO);
	if (data->pro.dup_check3 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
}

void	check_dap_creat(t_data *data, char **av, char **env)
{
	char	**str;

	if (ft_strnstr(av[1], "her_doc", 7) != NULL)
	{
		data->pro.dup_check2 = dup2(data->pro.file1, STDIN_FILENO);
		if (data->pro.dup_check2 == -1)
		{
			write(data->dap_out, "error dup2\n", 11);
			exit(1);
		}
	}
	check_file_access(data, av);
	dup_file(data);
	while (data->j < data->ac - 2)
	{
		creat_pipe(av[data->j], env, data);
		data->j++;
	}
	data->pro.path = get_path(env, av[data->ac - 2], data);
	str = ft_split(av[data->ac - 2], ' ');
	execve(data->pro.path, str, env);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*stp;

	i = 0;
	str = (unsigned char *) s2;
	stp = (unsigned char *) s1;
	if (n == 0)
		return (0);
	while (stp[i] && str[i] && i < (n - 1))
	{
		if (stp[i] != str[i])
			return (stp[i] - str[i]);
		i++;
	}
	return (stp[i] - str[i]);
}

// void	her_doc_(t_data *data)
// {
// 	while(1)
// 	{
// 		write(0, "heredoc", 7);
// 		if(ft_strnstr(read(0, )))
// 	}
// }

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data.ac = ac;
	data.j = 2;
	data.dap_out = dup(1);
	if (ac >= 5 && env[0] != NULL)
	{
		if (ft_strnstr(av[1], "her_doc", 7) != NULL)
		{
			data.limiter = av[1];
			data.pro.file1 = open("infile", O_CREAT | O_RDONLY, 00500);
			data.pro.dup_check2 = dup2(data.pro.file1, STDOUT_FILENO);
			if (data.pro.dup_check2 == -1)
			{
				write(data.dap_out, "error dup2\n", 11);
				exit(1);
			}
			her_doc_(&data);
			data.j = 3;
		}
		check_dap_creat(&data, av, env);
	}
	else
	{
		write(data.dap_out, "error!!", 7);
		exit(1);
	}
	return (0);
}
