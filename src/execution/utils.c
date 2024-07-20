/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:40 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:40 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

void	delete_token(void *content)
{
	t_token	*token;

	token = (t_token *) content;
	free(token->value);
	free(token);
	return ;
}

int	check_builtin(t_list *token)
{
	t_token	*arg;

	arg = (t_token *) token->content;
	if (!ft_strcmp(arg->value, "echo"))
		return (1);
	else if (!ft_strcmp(arg->value, "cd"))
		return (1);
	else if (!ft_strcmp(arg->value, "env"))
		return (1);
	else if (!ft_strcmp(arg->value, "unset"))
		return (1);
	else if (!ft_strcmp(arg->value, "pwd"))
		return (1);
	else if (!ft_strcmp(arg->value, "exit"))
		return (1);
	else if (!ft_strcmp(arg->value, "export"))
		return (1);
	else
		return (0);
}

int	execute_builtin(t_list *token, int fd)
{
	t_token	*arg;

	arg = (t_token *) token->content;
	if (!ft_strcmp(arg->value, "echo"))
		return (echo(token, fd));
	else if (!ft_strcmp(arg->value, "cd"))
		return (cd(token, fd));
	else if (!ft_strcmp(arg->value, "env"))
		return (env(token, fd));
	else if (!ft_strcmp(arg->value, "unset"))
		return (unset(token, fd));
	else if (!ft_strcmp(arg->value, "pwd"))
		return (pwd(token, fd));
	else if (!ft_strcmp(arg->value, "exit"))
		return (ft_exit(token, fd));
	else if (!ft_strcmp(arg->value, "export"))
		return (export(token, fd));
	else
		return (1);
}

int	set_underscore(void)
{
	t_token	*last;
	char	*arg;

	last = ft_lstlast(g_bin->cmd->content)->content;
	arg = ft_strdup("_=");
	if (ft_lstsize(g_bin->cmd) > 1)
		ft_strcat(&arg, "");
	else
		ft_strcat(&arg, last->value);
	ft_export(arg);
	free(arg);
	return (1);
}

char	**ft_get_env(void)
{
	size_t	i;
	char	**r;
	t_list	*tmp;
	size_t	j;

	tmp = g_bin->env;
	j = 0;
	i = ft_lstsize(g_bin->env);
	r = ft_calloc3(sizeof(char *), i + 1, "");
	while (tmp)
	{
		r[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	return (r);
}
