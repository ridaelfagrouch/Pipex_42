/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:47:57 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/21 11:34:32 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//****************************************************

int	ft_strcmp(char *s1, char *s2)
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
	wait(NULL);
	data->pro.dup_check1 = dup2(data->fd[0], STDIN_FILENO);
	if (data->pro.dup_check1 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
	close(data->fd[1]);
}

//****************************************************

void	creat_pipe(char *av, char *env[], t_data *data)
{
	if (pipe(data->fd) == -1)
	{
		write(data->dap_out, "error ocurred with opening the pipe\n", 36);
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
			here_doc_pipe(&data, av);
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
