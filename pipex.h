/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:30:35 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/14 01:49:38 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct d_process
{
	int		dup_check1;
	int		dup_check2;
	char	*path;
	int		file1;
	int		file2;
}	t_process;

typedef struct d_data
{
	char		**path_split;
	char		*path;
	char		**cmd_split;
	char		*cmd;
	char		*final_path;
	int			i;
	int			check_access;
	char		*ptr;
	int			dap_out;
	t_process	pro;
	
}	t_data;

char	*execv_fan(char **env, char *av);
void	child(int fd[2], char **av, char *env[], t_data *data);
void	parent(int fd[2], char **av, char *env[], t_data *data);
void	creat_pipe(char **av, char *env[], t_data *data);
void	free_split(char **ptr);
char	*get_path(char **env, char *av, t_data *data);

#endif