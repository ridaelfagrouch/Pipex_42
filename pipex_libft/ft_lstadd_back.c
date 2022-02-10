/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:34:35 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/14 18:15:21 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*root;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	root = *alst;
	while (root->next != NULL)
		root = root->next;
	root->next = new;
}
