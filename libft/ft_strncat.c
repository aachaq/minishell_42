/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:12:50 by abboutah          #+#    #+#             */
/*   Updated: 2023/01/21 10:12:50 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncat(char **dest, const char *src, size_t n)
{
	const size_t	dest_len = ft_strlen(*dest);
	const size_t	res_len = dest_len + n + 1;
	char *const		res = ft_calloc3(sizeof(char), res_len, "");

	ft_strlcpy(res, *dest, dest_len + 1);
	ft_strlcat(res + dest_len, src, n + 1);
	if (*dest != NULL)
		free(*dest);
	*dest = res;
	return (1);
}
