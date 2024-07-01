/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:30:17 by fli               #+#    #+#             */
/*   Updated: 2024/05/27 15:36:07 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*init;
	t_list	*n;
	void	*nc;

	if (!lst || !f || !del)
		return (NULL);
	init = NULL;
	while (lst != NULL)
	{
		nc = (*f)(lst->content);
		n = ft_lstnew(nc);
		if (!n)
		{
			(*del)(nc);
			ft_lstclear(&init, (*del));
			return (NULL);
		}
		ft_lstadd_back(&init, n);
		lst = lst->next;
	}
	return (init);
}
