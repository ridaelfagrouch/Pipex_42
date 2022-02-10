/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:35:41 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/11 15:01:19 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**ft_creat(char *s, char **result, char c, int row)
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

static int	str_row(char *tmp, char c)
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
