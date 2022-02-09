/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:52:17 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/14 18:20:25 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*root;
	int		len;

	root = lst;
	len = 0;
	while (root != NULL)
	{
		len++;
		root = root -> next;
	}
	return (len);
}
