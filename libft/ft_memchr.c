/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:36:19 by abboutah          #+#    #+#             */
/*   Updated: 2021/11/01 15:36:34 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (((unsigned char *)s)[index] == (unsigned char)c)
			return (((unsigned char *)s) + index);
		index++;
	}
	return (NULL);
}
