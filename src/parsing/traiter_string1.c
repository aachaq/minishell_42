/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traiter_string1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:56:09 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/21 13:52:19 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include "../../include/builtin.h"

char	*rechercher_var(char *str)
{
	t_list	*tab;
	int		signe;

	signe = 0;
	tab = g_bin->env;
	if (str[0] == '\0' || str[0] == '"' || str[0] == '\'')
		return (ft_strdup1("$"));
	if (str[0] == '?')
		return (ft_itoa1(g_bin->exit_status));
	while (tab)
	{
		if (ft_cmp(str, cut_var_string(tab->content)) == 0)
		{
			str = expand_var_str(tab->content);
			signe = 1;
			break ;
		}
		tab = tab->next;
	}
	if (signe == 0)
		return (ft_strdup1(""));
	return (str);
}

int	find_close_double_cout(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"')
			return (i);
		i++;
	}
	return (-1);
}

int	find_close_single_cout(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_str(char *str, int i, int start)
{
	t_exp	exp;

	exp.str2 = ft_substr1(str, i, ft_strlen(str));
	exp.str3 = ft_substr1(str, start, i - start);
	exp.str4 = rechercher_var(exp.str3);
	exp.str5 = ft_strjoin2(exp.str4, exp.str2);
	exp.str6 = ft_substr1(str, 0, start - 1);
	str = ft_strjoin2(exp.str6, exp.str5);
	return (str);
}

char	*expand(char *str)
{
	int		i;
	int		start;
	t_exp	exp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			start = i;
			exp.str1 = ft_substr1(str, start, ft_strlen(str));
			str = rechercher_var(exp.str1);
		}
		while (str[i])
		{
			if (str[i] == ' ' || str[i] == '\t' || str[i] == '\''
				|| str[i] == '"')
				str = get_str(str, i, start);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (str);
}
