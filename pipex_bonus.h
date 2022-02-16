/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:30:35 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/16 18:10:45 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

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
	int			j;
	int			ac;
	int			check_access;
	char		*ptr;
	int			dap_out;
	t_process	pro;
}	t_data;

char	*execv_fan(char **env, char *av);
void	free_split(char **ptr);
char	*get_path(char **env, char *av, t_data *data);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	new_lenght(char *str, size_t len, unsigned int new_start);
char	*if_star(void);
char	*ft_strdup(const char *str);
int		ft_len(const char *str);
char	**ft_split(char const *s, char c);
int		str_row(char *tmp, char c);
char	**ft_creat(char *s, char **result, char c, int row);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_setcheck(char c, char const *set);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_create_str(int len);

#endif