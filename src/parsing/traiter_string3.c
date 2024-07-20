/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traiter_string3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:05:35 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/21 14:01:34 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include	"../../include/builtin.h"

static long	ft_len(long n)
{
	long	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_string(long number, long len)
{
	long		s;
	char		*rtn;
	long		i;
	long		num;

	s = 0;
	if (number < 0)
	{
		num = number;
		s = 1;
		number = number * -1;
	}
	i = len;
	rtn = (char *)ft_leaks(len + 1);
	if (!rtn)
		return (NULL);
	while (number > 0)
	{
		rtn[--len] = 48 + number % 10;
		number = number / 10;
		if (number == 0 && s == 1)
			rtn[--len] = '-';
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*ft_itoa1(int n)
{
	long		len;
	char		*rtn2;

	if (n == 0)
		return (ft_strdup1("0"));
	len = ft_len(n);
	rtn2 = (ft_string(n, len));
	return (rtn2);
}

char	*cut_var_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr1(str, 0, i));
		i++;
	}
	return (str);
}

char	*traiter_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			str = fonction_double_cout(str, i - 1, i + 1);
			i = g_bin->i_memoir;
		}
		else if (str[i] == '\'')
		{
			str = fonction_single_cout(str, i - 1, i + 1);
			i = g_bin->i_memoir;
		}
		else if (str[i] == '$' && g_bin->exp_herdoc != 1)
		{
			str = expand_string(str, i - 1, i);
			i = g_bin->i_memoir;
		}
		if (str[i] != '\0' || i == -1)
			i++;
	}
	g_bin->exp_herdoc = 0;
	return (str);
}
