/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:58:34 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/20 13:40:28 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	n_flag(t_token *token)
{
	size_t	i;

	if (ft_strncmp(token->value, "-n", 2))
		return (0);
	i = 2;
	while (token->value[i])
	{
		if (token->value[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_list *token, int fd)
{
	int	n;

	if (token->next == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (g_bin->exit_status);
	}
	token = token->next;
	n = 0;
	if (n_flag(((t_token *) token->content)))
	{
			n = 1;
			token = token->next;
	}
	while (token)
	{
		ft_putstr_fd(((t_token *) token->content)->value, fd);
		if (token->next != NULL)
			ft_putstr_fd(" ", fd);
		token = token->next;
	}
	if (n == 0)
		ft_putstr_fd("\n", fd);
	return (g_bin->exit_status);
}
