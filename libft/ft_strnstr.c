/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:38:49 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/07 12:21:13 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
