/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:46:03 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/20 22:31:09 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/builtin.h"

void	ft_lstclear1(t_list **lst)
{
	t_list	*node;

	if (!lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = node;
	}
}

void	*ft_leaks(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	ft_lstadd_front(g_bin->leaks, ft_lstnew(ptr));
	return (ptr);
}
