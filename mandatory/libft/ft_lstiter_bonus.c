/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:03:49 by fli               #+#    #+#             */
/*   Updated: 2024/05/27 14:27:07 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*pos;

	if (!lst || !f)
		return ;
	pos = lst;
	if (lst && f)
	{
		while (pos)
		{
			(*f)(pos->content);
			pos = pos->next;
		}
	}
}
