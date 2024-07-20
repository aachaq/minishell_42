/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:05 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:05 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

static int	ft_atol(const char *str, long long *num)
{
	unsigned long long	n;
	size_t				i;

	i = 0;
	n = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(*num) = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i] - '0');
		if ((*num) == 1 && __LONG_LONG_MAX__ < n)
			return (0);
		if ((*num) == -1 && (unsigned long long)__LONG_LONG_MAX__ + 1 < n)
			return (0);
		i++;
	}
	(*num) *= n;
	return (1);
}

static int	num(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	set_exit(int status)
{
	g_bin->exit_status = status;
	return (g_bin->exit_status);
}

int	ft_exit(t_list *token, int fd)
{
	t_list		*tmp;
	t_token		*arg;
	long long	i;

	i = 1;
	tmp = token->next;
	if (fd == 2)
		ft_putendl_fd("exit", 2);
	if (tmp == NULL)
		exit(set_exit(0));
	arg = tmp->content;
	if (ft_atol(arg->value, &i) == 0)
		exit(erreur(255, "exit", arg->value, "numeric argument required"));
	if (num(arg->value) == 0)
		exit(erreur(255, "exit", arg->value, "numeric argument is required"));
	if (tmp->next != NULL)
		return (erreur(1, "exit", NULL, "too many arguments"));
	if (i < 0)
		i = (256 - ((i * -1) % 256));
	i = (i % 256);
	exit(set_exit(i));
	return (g_bin->exit_status);
}
