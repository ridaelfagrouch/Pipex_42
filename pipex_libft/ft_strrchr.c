/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:47:07 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/07 12:21:53 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	x;
	char	*str;

	i = 0;
	len = 0;
	str = (char *) s;
	x = (char) c;
	while (str[len])
		len++;
	while (len >= 0)
	{
		if (x == 0)
			return ((str + len));
		else if (str[len] == x)
			return (&str[len]);
		len--;
	}
	return (0);
}
