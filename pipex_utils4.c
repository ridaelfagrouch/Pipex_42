/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:19:42 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/14 20:20:28 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//**********************ft_strtrim******************************

int	ft_setcheck(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_setcheck(s1[start], set))
		start++;
	while (end > start && ft_setcheck(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

//**********************ft_split******************************

char	**ft_creat(char *s, char **result, char c, int row)
{
	int				j;
	size_t			len;
	int				i;
	unsigned int	start;

	j = -1;
	i = 0;
	start = 0;
	while (++j < row)
	{
		len = 0;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		result[j] = ft_substr(s, start, len);
		while (s[i] == c)
			i++;
		start = i;
	}
	free (s);
	return (result);
}

int	str_row(char *tmp, char c)
{
	int	count;

	count = 0;
	while (*tmp)
	{
		if (*tmp == c)
		{
			count++;
			while (*tmp == c)
				tmp++;
		}
		else
			tmp++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result ;
	char	*tmp ;
	char	*tmp1;
	char	to_tab[2];
	int		count;

	to_tab[0] = c;
	to_tab[1] = 0;
	result = NULL;
	if (!s)
		return (NULL);
	tmp = ft_strtrim(s, to_tab);
	if (!tmp)
		return (NULL);
	tmp1 = tmp;
	result = 0;
	count = str_row(tmp, c);
	if (*tmp1)
		count++;
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	result[count] = NULL;
	return (ft_creat(tmp1, result, c, count));
}
