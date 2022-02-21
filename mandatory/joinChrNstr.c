/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinChrNstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:19:23 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/20 18:24:52 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//**********************ft_strlen******************************

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

//**********************ft_strnstr******************************

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *) str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && (str[i + j] == to_find[j]) && ((i + j) < len))
		{
			if (to_find[j + 1] == '\0')
				return ((char *) &str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

//**********************ft_strjoin******************************

char	*ft_create_str(int len)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_create_str(len);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

//***************************ft_strchr*************************

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	x;

	i = 0;
	x = (char) c;
	str = (char *) s;
	while (str[i] >= 0)
	{
		if (str[i] == x)
			return (&str[i]);
		else if (str[i] == 0)
			break ;
		i++;
	}
	return (0);
}
