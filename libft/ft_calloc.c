/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:39:23 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/07 12:05:57 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	char		*res;

	res = NULL;
	i = 0;
	res = malloc(count * size);
	if (!res)
		return (0);
	while (i < count * size)
	{
		res[i] = 0;
		i++;
	}
	return ((void *) res);
}
