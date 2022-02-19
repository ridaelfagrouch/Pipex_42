/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:47:57 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/19 22:26:50 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	reset(void)
{
	write(0, "\033[0m", 5);
}

void	green(void)
{
	write(0, "\033[1;32m", 8);
}

//****************************************************

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

//****************************************************

static void	child(char *av, char *env[], t_data *data)
{
	char	**str;

	data->pro.path = NULL;
	data->pro.dup_check1 = dup2(data->fd[1], STDOUT_FILENO);
	if (data->pro.dup_check1 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(data->fd[0]);
	data->pro.path = get_path(env, av, data);
	str = ft_split(av, ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

static void	parent(t_data *data)
{
	data->pro.dup_check1 = dup2(data->fd[0], STDIN_FILENO);
	if (data->pro.dup_check1 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(data->fd[1]);
	wait(NULL);
}

//****************************************************

static void	check_file_access(t_data *data, char **av)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
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
	}
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
	if (pipe(data->fd) == -1)
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
		child(av, env, data);
	else
		parent(data);
}

//****************************************************

static void	dup_file(t_data *data, char **av)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		data->pro.dup_check2 = dup2(data->pro.file1, STDIN_FILENO);
		if (data->pro.dup_check2 == -1)
		{
			write(data->dap_out, "error dup2\n", 11);
			exit(1);
		}
	}
	data->pro.dup_check3 = dup2(data->pro.file2, STDOUT_FILENO);
	if (data->pro.dup_check3 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
}

//****************************************************

void	check_dap_creat(t_data *data, char **av, char **env)
{
	char	**str;

	check_file_access(data, av);
	dup_file(data, av);
	while (data->j < data->ac - 2)
	{
		creat_pipe(av[data->j], env, data);
		data->j++;
	}
	data->pro.path = get_path(env, av[data->ac - 2], data);
	str = ft_split(av[data->ac - 2], ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

void	here_doc_(t_data *data, char **av)
{
	char	*str;
	char	*ptr;
	int		i;

	(void)data;
	i = 0;
	while (1)
	{
		green();
		write(0, "heredoc> ", 9);
		reset();
		str = get_next_line(0);
		ptr = (char *) malloc(ft_strlen(str) - 1);
		if (!ptr)
			exit(1);
		while (str[i])
		{
			if (str[i] == '\n')
			{
				ptr[i] = '\0';
				break ;
			}
			ptr[i] = str[i];
			i++;
		}
		i = 0;
		if (ft_strcmp(ptr, av[2]) == 0)
			break ;
		else
		{
			write(data->fd[1], ptr, sizeof(ptr));
			free(ptr);
		}
	}
}

//****************************************************

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data.ac = ac;
	data.j = 2;
	data.dap_out = dup(1);
	if (ac >= 5 && env[0] != NULL)
	{
		if (ft_strcmp(av[1], "here_doc") == 0)
		{
			here_doc_(&data, av);
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
