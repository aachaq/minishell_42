/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traiter_string2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:02:45 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/21 13:37:48 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include "../../include/builtin.h"

char	*get_str_expnd(char *str, int end, int s1_end, int s2_start)
{
	t_exp	exp;

	exp.str1 = ft_substr1(str, s2_start, end - s2_start);
	exp.str2 = expand(exp.str1);
	g_bin->i_memoir = ft_strlen(exp.str2) + s1_end;
	exp.str3 = ft_substr1(str, end, ft_strlen(str));
	exp.str4 = ft_substr1(str, s2_start, end - s2_start);
	exp.str5 = expand(exp.str4);
	exp.str6 = ft_strjoin2(exp.str5, exp.str3);
	exp.str7 = ft_substr1(str, 0, s1_end + 1);
	str = ft_strjoin2(exp.str7, exp.str6);
	return (str);
}

char	*expand_string(char *str, int s1_end, int s2_start)
{
	int		i;
	int		end;

	i = s2_start + 1;
	end = 0;
	while (str[i])
	{
		if (is_alpha_number_indescor(str[i]) == 0)
		{
			if (str[i] == '?' && i > 0 && str[i - 1] == '$')
				end = i + 1;
			else
				end = i;
			break ;
		}
		if (str[i + 1] == '\0')
		{
			end = i + 1;
			break ;
		}
		i++;
	}
	return (get_str_expnd(str, end, s1_end, s2_start));
}

char	*expand_str_cout(char *str)
{
	int		i;
	int		s1_end;
	int		s2_start;
	char	*str2;

	i = 0;
	str2 = NULL;
	str2 = str;
	while (str2[i])
	{
		if (str2[i] == '$')
		{
			s1_end = i - 1;
			s2_start = i;
			str2 = expand_string(str2, s1_end, s2_start);
		}
		i++;
	}
	return (str2);
}

char	*fonction_single_cout(char *str, int s1_end, int s2_start)
{
	t_exp	exp;
	int		start_string;
	int		end_string;
	int		i;

	i = 0;
	start_string = s2_start;
	if (find_close_single_cout(str, s2_start) == -1)
	{
		erreur(1, str, NULL, "quote is not closed");
		g_bin->i_memoir = ft_strlen(str);
		return (str);
	}
	end_string = find_close_single_cout(str, s2_start) - 1;
	exp.str3 = ft_substr1(str, start_string, end_string - start_string + 1);
	g_bin->i_memoir = ft_strlen(exp.str3) + s1_end;
	exp.str4 = ft_substr1(str, end_string + 2, ft_strlen(str));
	exp.str5 = ft_substr1(str, start_string, end_string - start_string + 1);
	exp.str6 = ft_strjoin2(exp.str5, exp.str4);
	exp.str7 = ft_substr1(str, 0, s1_end + 1);
	exp.str2 = ft_strjoin2(exp.str7, exp.str6);
	return (exp.str2);
}

char	*fonction_double_cout(char *str, int s1_end, int s2_start)
{
	t_exp	exp;
	int		start_str;
	int		end_string;
	int		i;

	exp.str2 = str;
	start_str = s2_start;
	if (find_close_double_cout(exp.str2, s2_start) == -1)
	{
		erreur(1, str, NULL, "quote is not closed");
		g_bin->i_memoir = ft_strlen(exp.str2);
		return (str);
	}
	end_string = find_close_double_cout(str, s2_start) - 1;
	exp.str3_1 = ft_substr1(exp.str2, start_str, end_string - start_str + 1);
	exp.str3 = expand_str_cout(exp.str3_1);
	i = ft_strlen(exp.str3) + s1_end;
	exp.str4 = ft_substr1(exp.str2, end_string + 2, ft_strlen(exp.str2));
	exp.str5 = ft_substr1(exp.str2, start_str, end_string - start_str + 1);
	exp.str6 = expand_str_cout(exp.str5);
	exp.str7 = ft_strjoin2(exp.str6, exp.str4);
	exp.str8 = ft_substr1(exp.str2, 0, s1_end + 1);
	exp.str2 = ft_strjoin2(exp.str8, exp.str7);
	g_bin->i_memoir = i;
	return (exp.str2);
}
