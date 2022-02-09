/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:49:52 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/11 01:30:50 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static void	ft_remouv(char *s1)
{
	int	i;

	i = 0;
	while (i < (ft_len(s1) - 1))
	{
		s1[i] = s1[i + 1];
		i++;
	}
	s1[i] = '\0';
}

static void	ft_trim(char *s1, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (set[i])
	{
		if (s1[0] == set[i])
		{
			ft_remouv(s1);
			i = 0;
			continue ;
		}
		j = ft_len(s1) - 1;
		if (s1[j] == set[i])
		{
			s1[j] = '\0';
			i = 0;
			j--;
			continue ;
		}
		i++;
	}
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*s1_dup;
	char	*set_dup;
	char	*fin_tab;

	if (!s1 || !set)
		return (NULL);
	s1_dup = ft_strdup(s1);
	if (!s1_dup)
		return (NULL);
	set_dup = ft_strdup(set);
	if (!set_dup)
	{
		free(s1_dup);
		return (NULL);
	}
	ft_trim(s1_dup, set_dup);
	fin_tab = ft_strdup(s1_dup);
	free (s1_dup);
	free (set_dup);
	if (!fin_tab)
		return (0);
	return (fin_tab);
}
