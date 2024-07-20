/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:21 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/19 14:25:08 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"

char	*get_home(void)
{
	t_list	*tmp;

	tmp = g_bin->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
			return (ft_strdup(tmp->content + 5));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_getcwd(void)
{
	char	*r;
	t_list	*tmp;

	r = getcwd(NULL, 0);
	if (r != NULL)
		return (r);
	tmp = g_bin->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PWD=", 4))
		{
			r = ft_strdup(tmp->content + 4);
			break ;
		}
		tmp = tmp->next;
	}
	return (r);
}

char	*get_oldpwd(void)
{
	t_list	*tmp;

	tmp = g_bin->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
			return (ft_strdup(tmp->content + 7));
		tmp = tmp->next;
	}
	return (NULL);
}

int	erreur(int status, char *cmd, char *arg, char *d_error)
{
	ft_putstr_fd("minishell", 2);
	if (cmd != NULL && ft_putstr_fd(": ", 2))
		ft_putstr_fd(cmd, 2);
	if (arg != NULL && ft_putstr_fd(": ", 2))
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\'', 2);
	}
	if (d_error != NULL && ft_putstr_fd(": ", 2))
		ft_putstr_fd(d_error, 2);
	if (ft_strcmp(d_error, "quote is not closed") == 0)
		g_bin->lexer_erreur = 1;
	ft_putstr_fd("\n", 2);
	return (set_exit(status));
}
