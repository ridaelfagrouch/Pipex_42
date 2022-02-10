/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:32:09 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/11 01:31:56 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*if_star(void)
{
	char	*ptr;

	ptr = NULL;
	ptr = (void *)malloc(sizeof(char));
	if (!ptr)
		return (0);
	ptr[0] = '\0';
	return (ptr);
}

static size_t	new_lenght(char *str, size_t len, unsigned int new_start)
{
	size_t	i;

	i = 0;
	while (str[new_start] && i < len)
	{
		i++;
		new_start++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	char			*str;
	size_t			i;
	unsigned int	new_start;

	i = 0;
	ptr = NULL;
	if (!s)
		return (NULL);
	str = (char *) s;
	new_start = start;
	if (start > ft_strlen(s))
		return (if_star());
	ptr = (void *)malloc((new_lenght(str, len, new_start) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while ((i < len) && (str[start] != '\0'))
		ptr[i++] = str[start++];
	ptr[i] = '\0';
	return (ptr);
}
