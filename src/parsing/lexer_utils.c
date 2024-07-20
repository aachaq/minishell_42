/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:03:53 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/15 16:07:44 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include    "../../include/lexer.h"
#include "../../include/builtin.h"
#include "../../libft/libft.h"

void	*ft_calloc1(size_t count, size_t size)
{
	void	*re;

	re = ft_leaks(count * size);
	if (!re)
		return ((void *)0);
	ft_memset(re, 0, count * size);
	return (re);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	s3 = ft_leaks(i + j + 1);
	if (!s3)
		return ((char *)0);
	s3[0] = '\0';
	ft_strcat(&s3, s1);
	ft_strcat(&s3, s2);
	return (s3);
}

char	*ft_substr1(char *s, int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*s1;

	if (!s)
		return ((char *)0);
	i = 0;
	l = ft_strlen(s + start);
	if (l < len)
		len = l;
	s1 = (char *)ft_leaks(len + 1);
	if (!s1)
		return ((char *)0);
	while (s[i] != '\0' && len > i && (size_t)start <= ft_strlen(s))
	{
		s1[i] = s[start];
		i++;
		start++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strdup1(char *s)
{
	int		i;
	int		len;
	char	*buff;

	i = 0;
	len = ft_strlen(s);
	buff = ft_leaks(sizeof(char) * len + 1);
	if (!buff)
		return (0);
	while (s[i])
	{
		buff[i] = s[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
