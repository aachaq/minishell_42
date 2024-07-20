/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:37:33 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/19 14:11:06 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *)malloc(nmemb * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

static int	is_invalid_input(size_t sz_, size_t count)
{
	if (SIZE_MAX <= sz_ || SIZE_MAX <= count)
		return (1);
	if (sz_ && SIZE_MAX / sz_ <= count)
		return (1);
	return (0);
}

void	*ft_calloc3(size_t sz_, size_t count, const char *error_msg)
{
	void	*res;

	if (is_invalid_input(sz_, count))
		ft_exit_with_error(error_msg, errno);
	res = malloc(sz_ * count);
	if (!res)
		ft_exit_with_error(error_msg, errno);
	ft_bzero(res, (sz_ * count));
	return (res);
}
