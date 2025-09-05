/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:20:00 by mmedjahe          #+#    #+#             */
/*   Updated: 2023/11/20 15:15:57 by mmedjahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nlst;

	if (!lst || !del)
		return ;
	while (lst && *lst)
	{
		nlst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nlst;
	}
	*lst = NULL;
}
