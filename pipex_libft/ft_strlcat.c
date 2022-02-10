/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:29:16 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/07 12:16:24 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	i;
	char	*str;

	i = 0;
	ls = 0;
	ld = 0;
	str = (char *) src;
	while (str[ls])
		ls++;
	while (dest[ld])
		ld++;
	if (size < ld)
		ls += size;
	else
		ls += ld;
	while (src[i] != '\0' && ld + 1 < size)
	{
		dest[ld] = str[i];
		ld++;
		i++;
	}
	dest[ld] = '\0';
	return (ls);
}
