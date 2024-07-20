/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traiter_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:27:32 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/15 23:13:40 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include "../../include/builtin.h"
#include "../../libft/libft.h"

int	count_double_cout(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count);
}

int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*expand_var_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			str = ft_substr1(str, i, ft_strlen(str));
			return (str);
		}
		i++;
	}
	return (ft_strdup1(""));
}

int	cmp(char *s1)
{
	if (s1[0] == '\0')
		return (0);
	return (1);
}

int	is_alpha_number_indescor(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	return (0);
}
