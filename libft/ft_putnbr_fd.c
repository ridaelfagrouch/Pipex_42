/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:52:43 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/11 17:54:27 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 10 && n >= 0)
		{
			ft_putchar_fd((n + '0'), fd);
		}
		else if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd((n * -1), fd);
		}
		else if (n >= 10)
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putchar_fd((n % 10 + '0'), fd);
		}
	}
}
