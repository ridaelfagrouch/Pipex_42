/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:57:32 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/11 14:58:07 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_itoi(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*check_itoi(int n)
{
	char	*str;

	if (n == 0)
		str = ft_strdup("0");
	if (n == -2147483648)
		str = ft_strdup("-2147483648");
	return (str);
}

static unsigned int	check_n_sign(int n)
{
	unsigned int	j;

	if (n < 0)
		j = n * -1;
	else
		j = n;
	return (j);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	j;
	char			*str;

	str = NULL;
	if (n == 0 || n == -2147483648)
		return (check_itoi(n));
	j = check_n_sign(n);
	len = len_itoi(j);
	if (n < 0)
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	while (j > 0)
	{
		str[len] = (j % 10) + '0';
		j = j / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
