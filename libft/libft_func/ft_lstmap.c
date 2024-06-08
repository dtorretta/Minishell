/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:05:50 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 19:57:11 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*creates a new list resulting from the application of f to each element*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*result;
	void	*v;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		v = f(lst->content);
		result = ft_lstnew(v);
		if (!result)
		{
			del(v);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, result);
		lst = lst->next;
	}
	return (new);
}
