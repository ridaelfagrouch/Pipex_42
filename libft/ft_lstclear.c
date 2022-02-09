/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:23:10 by rel-fagr          #+#    #+#             */
/*   Updated: 2021/11/14 18:16:25 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*root;
	t_list	*ptr;

	root = NULL;
	ptr = *lst;
	if (!*lst)
		*lst = NULL;
	while (ptr != NULL)
	{
		root = ptr;
		del(root->content);
		ptr = ptr -> next;
		free(root);
	}
	*lst = NULL;
}
